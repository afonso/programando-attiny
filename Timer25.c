#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

//bits dos pinos de I/O
#define BOTAO	_BV(PB3)
#define LED		_BV(PB4)

//valor para contar aprox 1s
#define TEMPO_1SEG	20

//programa principal
int main(void) {
	//pino de LED é de saida
	DDRB |= LED;
	PORTB = 0;

	//configura timer 0
	TCCR0A = 0; //modo normal: overflow a cada 256 contagens
	TCCR0B = _BV(CS01) | _BV(CS00); //usar clkIO/64: int a cada 64*256/1000ms = 16,384ms
	TIMSK = _BV(TOIE0); //interromper no overflow

	//permite interrupcoes
	sei();

	//loop infinito
	for(;;){
		set_sleep_mode(SLEEP_MODE_IDLE);
		sleep_mode();
	}

}

//tratamento da interrupcao do timer 0
ISR (TIMER0_OVF_vect){
	static unsigned char cnt = TEMPO_1SEG;
	
	//aguarda 1 segundo
	if(--cnt != 0)
		return;
	cnt = TEMPO_1SEG;

	//pisca o LED
	PORTB ^= LED;
}