#include "print.h"
#include "string.h"

namespace ns_util {

	KPrint& KPrint::operator()(const char* aCStr)
	{
		m_str = aCStr;
		m_str_len = strlen(aCStr);
		m_next_pos = 0;
		m_nl = false;

		impl_skip_pos();
	}

	KPrint& KPrint::nl()
	{
		m_nl = true;

		if( m_next_pos>=m_str_len ) {
			impl_print_newline();
		}

		return *this;
	}

	void KPrint::impl_skip_pos()
	{
		for(; m_next_pos<m_str_len; m_next_pos++) {
			if( '%' == m_str[m_next_pos] ) {
				m_next_pos++;
				return;
			}
			k_dbg_putchar(m_str[m_next_pos]);
		}

		if( m_nl ) {
			impl_print_newline();
		}
	}

	void KPrint::impl_print_newline()
	{
		k_dbg_putchar('\r');
		k_dbg_putchar('\n');
	}

	KPrint::format_info_t KPrint::get_format_info(num_format_e aFormat)
	{
		format_info_t ret;

		switch(aFormat)
		{
		case num_format_e::BINARY:
			ret.divider = 2;
			ret.prefix[1] = 'b';
			ret.prefix[0] = '0';
			ret.prefix_count = 2;
			ret.convert = &KPrint::digit_to_bin;
			break;
		case num_format_e::DECIMAL:
			ret.divider = 10;
			ret.prefix[1] = '\0';
			ret.prefix[0] = '\0';
			ret.prefix_count = 0;
			ret.convert = &KPrint::digit_to_dec;
			break;
		case num_format_e::HEX:
			ret.divider = 16;
			ret.prefix[1] = 'x';
			ret.prefix[0] = '0';
			ret.prefix_count = 2;
			ret.convert = &KPrint::digit_to_hex;
			break;
		}

		return ret;
	}



	char KPrint::digit_to_hex(int digit)
	{
	   switch(digit & 0xF) {
		  case 0x0: return '0';
		  case 0x1: return '1';
		  case 0x2: return '2';
		  case 0x3: return '3';
		  case 0x4: return '4';
		  case 0x5: return '5';
		  case 0x6: return '6';
		  case 0x7: return '7';
		  case 0x8: return '8';
		  case 0x9: return '9';
		  case 0xA: return 'A';
		  case 0xB: return 'B';
		  case 0xC: return 'C';
		  case 0xD: return 'D';
		  case 0xE: return 'E';
		  case 0xF: return 'F';
		}

	   return  '?';
	}

	char KPrint::digit_to_dec(int aDigit)
	{
		return (aDigit < 0 || aDigit > 9) ? '?' : '0' + aDigit;
	}



	char KPrint::digit_to_bin(int digit)
	{
		if( digit )
			return '1';
		return '0';
	}

	KPrint console;
}
