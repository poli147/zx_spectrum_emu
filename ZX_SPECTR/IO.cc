#include "IO.h"
void IO::write(unsigned address, uint8_t value)
{
	if (address & 1) {
		if ((address & 0x8002) == 0) _port_fd = value;
		else if ((address & 0xff) == 0xff) _port_ff = value;}
	else {_port_fe = value;

		int level = (_port_fe >> 3) & 0x03;
		switch (level) {
			case 0x00: _adrv->set_level(-16384 - 8192); break;
			case 0x01: _adrv->set_level(-16384); break;
			case 0x02: _adrv->set_level(16384); break;
			case 0x03: _adrv->set_level(16384 + 8192); break;
			default: ;}}}
uint8_t IO::read(unsigned address) const
{
	uint8_t a = (address >> 8);
	uint8_t p = (address & 0xff);
	/*if (p == 0xfe) {
		switch (a) {
		case 0x7f: return _key_matrix[0];
		case 0xbf: return _key_matrix[1];
		case 0xdf: return _key_matrix[2];
		case 0xef: return _key_matrix[3];
		case 0xf7: return _key_matrix[4];
		case 0xfb: return _key_matrix[5];
		case 0xfd: return _key_matrix[6];
		case 0xfe: return _key_matrix[7];
		default: return 0;
		}*/
    switch (p) {
    case 0xfe: {
            uint8_t keys = 0x1f;
            for (uint8_t i = 0; i < 8; i++) {
                if ((a & (1 << i)) == 0) keys &= _key_matrix[7 - i];}
            return (_ear << 6) | keys; }
    case 0xff:return _port_ff; default: break;}
	return 0;
}
void IO::keydown(unsigned row, unsigned col)
{
	_key_matrix[row] &= ~(1 << col);}
void IO::keyup(unsigned row, unsigned col)
{
	_key_matrix[row] |= (1 << col);}
