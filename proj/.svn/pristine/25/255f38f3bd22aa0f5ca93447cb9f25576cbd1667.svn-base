#include "rtc_macros.h"

.intel_syntax

.global _get_min_rtc
.global _get_hour_rtc
.global _get_day_rtc
.global _get_month_rtc
.global _get_year_rtc

.text

_get_min_rtc:
	xor eax, eax
	movb al, RTC_MIN_ADDR
	outb RTC_ADDR_REG, al
	inb al, RTC_DATA_REG
	ret

_get_hour_rtc:
	xor eax, eax
	movb al, RTC_HOUR_ADDR
	outb RTC_ADDR_REG, al
	inb al, RTC_DATA_REG
	ret

_get_day_rtc:
	xor eax, eax
	movb al, RTC_DAY_ADDR
	outb RTC_ADDR_REG, al
	inb al, RTC_DATA_REG
	ret


_get_month_rtc:
	xor eax, eax
	movb al, RTC_MONTH_ADDR
	outb RTC_ADDR_REG, al
	inb al, RTC_DATA_REG
	ret


_get_year_rtc:
	xor eax, eax
	movb al, RTC_YEAR_ADDR
	outb RTC_ADDR_REG, al
	inb al, RTC_DATA_REG
	ret
