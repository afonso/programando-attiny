PROGNAME=PWM
DEVICE=attiny25
AVRDUDEFLAGS=-c usbasp -p ${DEVICE}

all:	${PROGNAME}.hex

program:	${PROGNAME}-upload

${PROGNAME}.hex: ${PROGNAME}.obj
	avr-objcopy -R .eeprom -O ihex ${PROGNAME}.obj ${PROGNAME}.hex

${PROGNAME}.obj: ${PROGNAME}.c
	avr-gcc -g -Os -Wall -mcall-prologues -mmcu=${DEVICE} \
	-Wl,-Map,${PROGNAME}.map -o ${PROGNAME}.obj ${PROGNAME}.c

${PROGNAME}-upload: ${PROGNAME}.hex
	avrdude ${AVRDUDEFLAGS} -U flash:w:${PROGNAME}.hex:i