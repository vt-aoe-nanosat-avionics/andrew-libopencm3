
#include <libopencm3/stm32/quadspi.h>

void quadspi_enable(void)
{
	QUADSPI_CR |= QUADSPI_CR_EN;
}

void quadspi_disable(void)
{
	QUADSPI_CR &= ~QUADSPI_CR_EN;
}

void quadspi_set_flash_size(uint8_t fsize)
{
	QUADSPI_DCR |= fsize << QUADSPI_DCR_FSIZE_SHIFT;
}

void quadspi_set_high_time(uint8_t high_time)
{
	QUADSPI_DCR |= (high_time << QUADSPI_DCR_CSHT_SHIFT);
}

void quadspi_clear_flag(uint8_t flag)
{
	QUADSPI_FCR |= flag;
}

void quadspi_set_prescaler(uint8_t prescaler)
{
	QUADSPI_CR |= prescaler << QUADSPI_CR_PRESCALE_SHIFT;
}

void quadspi_enable_sample_shift(void)
{
	QUADSPI_CR |= QUADSPI_CR_SSHIFT;
}

void quadspi_disable_sample_shift(void)
{
	QUADSPI_CR &= ~QUADSPI_CR_SSHIFT;
}

uint8_t quadspi_get_busy(void)
{
	return QUADSPI_SR & QUADSPI_SR_BUSY;
}

void quadspi_set_fmode(uint8_t mode)
{
	QUADSPI_CCR |= mode << QUADSPI_CCR_FMODE_SHIFT;
}

void quadspi_set_data_mode(uint8_t mode)
{
	QUADSPI_CCR |= mode << QUADSPI_CCR_DMODE_SHIFT;
}

void quadspi_set_num_dummy_cycles(uint8_t cycles)
{
	QUADSPI_CCR |= cycles << QUADSPI_CCR_DCYC_SHIFT;
}

void quadspi_set_alternate_byte_size(uint8_t size)
{
	QUADSPI_CCR |= size << QUADSPI_CCR_ABSIZE_SHIFT;
}

void quadspi_set_alternate_byte_mode(uint8_t mode)
{
	QUADSPI_CCR |= mode << QUADSPI_CCR_ABMODE_SHIFT;
}

void quadpsi_set_address_size(uint8_t size)
{
	QUADSPI_CCR |= size << QUADSPI_CCR_ADSIZE_SHIFT;
}

void quadspi_set_address_mode(uint8_t mode)
{
	QUADSPI_CCR |= mode << QUADSPI_CCR_ADMODE_SHIFT;
}

void quadspi_set_instruction_mode(uint8_t mode)
{
	QUADSPI_CCR |= mode << QUADSPI_CCR_IMODE_SHIFT;
}

void quadspi_set_instruction(uint8_t instruction)
{
	QUADSPI_CCR |= instruction << QUADSPI_CCR_INST_SHIFT;
}

void quadspi_write_data(uint8_t data)
{
	QUADSPI_DR = data;
}

void quadspi_set_fifo_threshold(uint8_t threshold)
{
	QUADSPI_CR |= threshold << QUADSPI_CR_FTHRES_SHIFT;
}




void quadspi_send_instruction(uint8_t instruction, uint8_t dataMode)
{
	while(quadspi_get_busy()) {
		;
	}
	quadspi_clear_flag(QUADSPI_FCR_CTOF | QUADSPI_FCR_CSMF | QUADSPI_FCR_CTCF | QUADSPI_FCR_CTEF);
	
	quadspi_set_fmode(QUADSPI_CCR_FMODE_IWRITE);
	quadspi_set_instruction_mode(dataMode);
	quadspi_set_instruction(instruction);

	while(!(QUADSPI_SR & QUADSPI_SR_TCF)) {
		;
	}
	quadspi_clear_flag(QUADSPI_FCR_CTOF | QUADSPI_FCR_CSMF | QUADSPI_FCR_CTCF | QUADSPI_FCR_CTEF);
}

void quadspi_write_register(uint8_t instruction, uint8_t dataMode, uint8_t data)
{
	while(quadspi_get_busy()) {
		;
	}
	quadspi_clear_flag(QUADSPI_FCR_CTOF | QUADSPI_FCR_CSMF | QUADSPI_FCR_CTCF | QUADSPI_FCR_CTEF);

	quadspi_set_fifo_threshold(1);
	quadspi_set_fmode(QUADSPI_CCR_FMODE_IWRITE);
	quadspi_set_data_mode(dataMode);
	quadspi_set_instruction_mode(dataMode);
	quadspi_set_instruction(instruction);
	quadspi_write_data(data);

	while(!(QUADSPI_SR & QUADSPI_SR_TCF)) {
		;
	}
	quadspi_clear_flag(QUADSPI_FCR_CTOF | QUADSPI_FCR_CSMF | QUADSPI_FCR_CTCF | QUADSPI_FCR_CTEF);
}