#ifndef UTIL_PRINT_H_
#define UTIL_PRINT_H_

#include "../typedefs.h"
#include <type_traits>
#include <functional>


namespace ns_util {

	class KPrint
	{
	public:
		KPrint& operator()(const char* aCStr);

		static char digit_to_hex(int digit);
		static char digit_to_bin(int digit);
		static char digit_to_dec(int aDigit);



	protected:
		const char* m_str;
		size_t m_str_len;
		int m_next_pos;
		bool m_nl;

		void impl_skip_pos();
		void impl_print_newline();
		void impl_print_prefix(num_format_e aFormat);

		typedef char (*num_convert_f)(int);

		struct format_info_t {
			size_t divider;
			char prefix[2];
			size_t prefix_count;
			num_convert_f convert;
		};

		static format_info_t get_format_info(num_format_e aFormat);

	public:

		KPrint& nl();

		template<typename T>
		KPrint& arg_num(T aVal, num_format_e aFormat=num_format_e::DECIMAL)
		{
			const size_t output_capacity = sizeof(aVal)*8; //2 for prefix
			const format_info_t format = get_format_info(aFormat);
			u8_t outbuff[output_capacity];
			size_t output_count = 0;
			auto val_copy = aVal;

			do {
				outbuff[output_count] = format.convert( val_copy % format.divider );
				val_copy /= format.divider;
				output_count++;
			} while( val_copy );

			for(size_t iPrefx=0; iPrefx<format.prefix_count; iPrefx++) {
				k_dbg_putchar( format.prefix[iPrefx] );
			}

			for(int iPos=output_count-1; iPos >= 0; iPos--) {
				k_dbg_putchar( outbuff[iPos] );
			}

			impl_skip_pos();

			return *this;
		}

		KPrint& arg_str(const char* aStr)
		{
			while( '\0' != *aStr ) {
				k_dbg_putchar( *aStr );
				aStr++;
			}

			impl_skip_pos();

			return *this;
		}
	};



	extern KPrint console;

}

#endif /* UTIL_PRINT_H_ */
