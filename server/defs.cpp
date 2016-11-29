#include "defs.h"
#include <cassert>

#define is_bigendian() ( (*(char*)&i) == 0 )


WriteBuffer::WriteBuffer(size_t numbytes)
{
	buf.data = std::make_unique<std::uint8_t[]>(numbytes);
	buf.size = numbytes;
	buf.index = 0;
}

void WriteBuffer::serialize_int(std::uint32_t value)
{
	std::assert(buffer.index + 4 <= size);
	if( is_bigendian() )
		*((uint32_t*)(buffer.data + buffer.index)) = bswap(value);
	else
		*((uint32_t*)(buffer.data + buffer.index)) = value;

	buffer.index += 4;
}

void WriteBuffer::serialize_char(char value)
{
	std::assert(buffer.index + 4 <= size);
	if (is_bigendian())
		*((uint32_t*)(buffer.data + buffer.index)) = bswap(value);
	else
		*((uint32_t*)(buffer.data + buffer.index)) = value;

	buffer.index += 4;
}