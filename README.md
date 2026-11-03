# ATmega32 Smart Home

A bare-metal smart-home controller for the **ATmega32** microcontroller, written in C.

> **This project was the final project of the Embedded Systems Workshop organized by the Aviation Club.**

The system monitors room temperature and light level, drives a fan and RGB lighting automatically, and raises a critical alarm when fire is detected.

---

## Features

| Feature | Description |
|---|---|
| **Temperature monitoring** | An LM35 sensor is read through the ADC and shown in °C on the LCD. |
| **Automatic fan control** | A DC motor fan runs at 0, 25, 50, 75 or 100% speed (hardware PWM) depending on temperature. |
| **Ambient light monitoring** | An LDR is read through the ADC and shown as a percentage on the LCD. |
| **Automatic lighting** | Three LEDs (red, green, blue) turn on progressively as the room gets darker. |
| **Fire / flame alarm** | A flame sensor on an external interrupt immediately triggers an alert: fan and lights off, "Critical alert!" on the LCD and a pulsing buzzer for as long as the flame is detected. |
| **Live LCD dashboard** | A 16x2 character LCD shows temperature, light level and fan status. |

---

## How it works

### Fan speed (temperature based)

| Temperature | Fan |
|---|---|
| below 25 °C | OFF |
| 25 - 29 °C | ON, 25% |
| 30 - 34 °C | ON, 50% |
| 35 - 39 °C | ON, 75% |
| 40 °C and above | ON, 100% |

The fan always spins clockwise. Speed is set by the duty cycle of Timer0's Fast PWM output.

### Lighting (light level based)

| LDR reading | LEDs on |
|---|---|
| above 70% (bright) | none |
| 51 - 70% | red |
| 17 - 50% | red + green |
| 16% or below (dark) | red + green + blue |

### Flame alert

The flame sensor is wired to **INT0** and configured for a rising edge. When it fires, the interrupt handler `AlertMode()`:

1. Stops the fan.
2. Turns all three LEDs off.
3. Clears the LCD and prints `Critical alert!`.
4. Beeps the buzzer (100 ms on / 100 ms off) while the flame sensor pin stays high.

When the flame is gone, the handler returns and normal operation resumes.

### LCD layout

```
Row 0:   Fan is ON 75%
Row 1: Temp=36 LDR=48%
```

---

## Hardware

### Components

- ATmega32 microcontroller running at **16 MHz**
- 16x2 character LCD (HD44780 compatible), 8-bit mode
- LM35 temperature sensor
- LDR (light dependent resistor) in a voltage divider
- Flame sensor module (digital output)
- DC motor (fan) with an H-bridge / motor driver (e.g. L293D or L298N)
- Active buzzer
- 3 LEDs (red, green, blue) with series resistors

### Pin map

| Peripheral | ATmega32 pin(s) | Notes |
|---|---|---|
| LDR | **PA0** (ADC0) | Analog input |
| LM35 | **PA1** (ADC1) | Analog input |
| LCD data D0-D7 | **PC0 - PC7** | 8-bit data bus |
| LCD RS | **PD0** | Register select |
| LCD E | **PD1** | Enable (RW is not driven: tie it to GND) |
| Flame sensor | **PD2** (INT0) | Rising-edge external interrupt |
| Buzzer | **PD3** | Digital output |
| Motor IN1 | **PB0** | Direction |
| Motor IN2 | **PB1** | Direction |
| Motor enable | **PB3** (OC0) | Timer0 Fast PWM output |
| Red LED | **PB5** | |
| Green LED | **PB6** | |
| Blue LED | **PB7** | |

Pins are chosen in `APP/main.c` and in `HAL/LCD.h`, so they are easy to change.

---

## Software architecture

The code follows a layered architecture, so each layer only talks to the one directly below it.

```
Final Project Smart Home/
├── APP/
│   └── main.c            Application logic (the smart-home behaviour)
├── HAL/                  Hardware Abstraction Layer: drivers for external devices
│   ├── LCD.c/.h          16x2 LCD driver (8-bit mode)
│   ├── LED.c/.h          LED on / off / toggle
│   ├── LDR.c/.h          Light sensor -> percentage
│   ├── LM35.c/.h         Temperature sensor -> °C
│   ├── Motor.c/.h        DC motor direction + PWM speed
│   ├── Flame.c/.h        Flame sensor + interrupt registration
│   └── Buzzer.c/.h       Buzzer on / off
├── MCAL/                 Microcontroller Abstraction Layer: drivers for on-chip peripherals
│   ├── DIO.c/.h          Digital I/O (pin direction, read, write, toggle)
│   ├── ADC.c/.h          10-bit ADC
│   ├── EXT_INTERRUPT.c/.h  External interrupts INT0 / INT1 / INT2
│   └── TIMER0.c/.h       Timer0 (normal, CTC, phase-correct and Fast PWM modes)
└── LIB/
    ├── STD_TYPES.h       Fixed-width type aliases (u8, u16, u32, ...)
    └── BIT_MATH.h        Bit manipulation macros (SET_BIT, CLR_BIT, GET_BIT, ...)
```

### MCAL drivers

- **DIO**: sets pin direction and reads / writes / toggles pins on ports A to D.
- **ADC**: 10-bit conversions, AVCC (5 V) reference, right-adjusted result, prescaler 128, single-conversion mode. The application uses the blocking `ADC_u16GetResultSync()`. Configuration (reference, adjustment, trigger source, prescaler) is done with `#define`s at the top of `ADC.h`. An interrupt-driven mode with a callback is also implemented.
- **External interrupts**: init, enable and disable for INT0 / INT1 / INT2 with selectable sense control (low level, any change, falling edge, rising edge) and a callback registered per interrupt.
- **Timer0**: configured in `TIMER0.h` (currently **Fast PWM**, non-inverting, prescaler 1024). Also supports normal and CTC modes with a time-based API (`Timer0_vSetTime`) and a callback.

### HAL drivers

- **LCD**: initialization, commands, characters, strings, cursor positioning (`LCD_MoveCursor`), `LCD_SendString_MV_CR` (move then print), clear and scroll.
- **LED**: `led_init`, `led_on`, `led_off`, `led_toggle` on any port / pin.
- **LDR**: `LDR_u8GetPrecent()` converts the ADC reading into a percentage using a linear scale factor.
- **LM35**: `LM35_u16getCelsius()` converts the ADC reading to °C (10 mV per °C with a 5 V reference).
- **Motor**: `Motor_init`, `Motor_ON(direction, duty%)` and `Motor_OFF`. Supports both directions (`motor_clockwise_direction`, `motor_anticlockwise_direction`).
- **Flame**: `Flame_init(int_number, callback)` sets up the pin, rising-edge trigger and interrupt, and `FLAME_PinState()` reads the sensor. INT0, INT1 and INT2 are supported.
- **Buzzer**: `BUZZER_init`, `BUZZER_ON`, `BUZZER_OFF`.
