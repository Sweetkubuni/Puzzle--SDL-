#pragma once
#include <cstdint>
#include <memory>
#include <type_traits>
#define MAX_BLOCKS  21
#define MAX_MSG_LEN 8
struct Buffer
{
	std::unique_ptr<std::uint8_t []> data;     // pointer to buffer data
	int size;                // size of buffer data (bytes)
	int index;               // index of next byte to be read/written

};

class	WriteBuffer
{
	Buffer buf;
public:
	WriteBuffer(size_t numbytes );

	void serialize_int(std::uint32_t value);

	void serialize_char(char value);
};

class	ReadBuffer
{
	Buffer buf;
public:
	ReadBuffer();

	bool serialize_int(std::uint32_t & value);

	bool serialize_char(char & value);
};
struct session_request
{
	char request[8];
	unsigned int  session_token;

	template <typename stream > 
	void serialize(stream & ss)
	{
		if (std::is_same<stream, WriteBuffer>::value)
		{
			for (int i = 0; i < MAX_MSG_LEN; i++)
				ss.serialize(request[i]);
			ss.serialize_int(session_token);
		}

		if (std::is_same<stream, ReadBuffer>::value)
		{
			for (int i = 0; i < MAX_MSG_LEN; i++)
				ss.serialize(request[i]);
			ss.serialize_int(session_token);
		}
	}
};

struct session_response
{
	char response[8];
	unsigned int field[MAX_BLOCKS];

	template <typename stream >
	void serialize(stream & ss)
	{
		if (std::is_same<stream, WriteBuffer>::value)
		{
			for (int i = 0; i < MAX_MSG_LEN; i++)
				ss.serialize(request[i]);
			for (int i = 0; i < MAX_BLOCKS; i++)
			    ss.serialize_int(field[i]);
		}

		if (std::is_same<stream, ReadBuffer>::value)
		{
			for (int i = 0; i < MAX_MSG_LEN; i++)
				ss.serialize(request[i]);
			for (int i = 0; i < MAX_BLOCKS; i++)
				ss.serialize_int(field[i]);
		}
	}
};

struct server_update
{
	char msg[8];
	unsigned int  session_token;
	unsigned int blocks[3];

	template <typename stream >
	void serialize(stream & ss)
	{
		if (std::is_same<stream, WriteBuffer>::value)
		{
			for (int i = 0; i < MAX_MSG_LEN; i++)
				ss.serialize(request[i]);
			for (int i = 0; i < MAX_BLOCKS; i++)
				ss.serialize_int(field[i]);
		}

		if (std::is_same<stream, ReadBuffer>::value)
		{
			for (int i = 0; i < MAX_MSG_LEN; i++)
				ss.serialize(request[i]);
			for (int i = 0; i < MAX_BLOCKS; i++)
				ss.serialize_int(field[i]);
		}
	}
};

struct client_update
{
	char msg[8];
	unsigned int health;
};

