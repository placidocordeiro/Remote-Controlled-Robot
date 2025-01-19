#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define MOTOR1_DIR_PIN 2
#define MOTOR1_PWM_PIN 3
#define MOTOR2_DIR_PIN 4
#define MOTOR2_PWM_PIN 5

void motor_init() {
    gpio_init(MOTOR1_DIR_PIN);
    gpio_set_dir(MOTOR1_DIR_PIN, GPIO_OUT);
    
    gpio_init(MOTOR2_DIR_PIN);
    gpio_set_dir(MOTOR2_DIR_PIN, GPIO_OUT);

    gpio_set_function(MOTOR1_PWM_PIN, GPIO_FUNC_PWM);
    gpio_set_function(MOTOR2_PWM_PIN, GPIO_FUNC_PWM);
    
    uint slice_num1 = pwm_gpio_to_slice_num(MOTOR1_PWM_PIN);
    uint slice_num2 = pwm_gpio_to_slice_num(MOTOR2_PWM_PIN);
    
    pwm_set_wrap(slice_num1, 255);
    pwm_set_wrap(slice_num2, 255);
    
    pwm_set_enabled(slice_num1, true);
    pwm_set_enabled(slice_num2, true);
}

void set_motor_direction(int motor, int direction) {
    if (motor == 1) {
        gpio_put(MOTOR1_DIR_PIN, direction);
    } else if (motor == 2) {
        gpio_put(MOTOR2_DIR_PIN, direction);
    }
}

void set_motor_speed(int motor, int speed) {
    uint slice_num;
    if (motor == 1) {
        slice_num = pwm_gpio_to_slice_num(MOTOR1_PWM_PIN);
    } else {
        slice_num = pwm_gpio_to_slice_num(MOTOR2_PWM_PIN);
    }

    pwm_set_gpio_level(motor == 1 ? MOTOR1_PWM_PIN : MOTOR2_PWM_PIN, speed);
}

int main() {
    motor_init();
    
    // Set both motors to move forward with half speed
    set_motor_direction(1, 1);
    set_motor_direction(2, 1);
    set_motor_speed(1, 128);
    set_motor_speed(2, 128);

    sleep_ms(5000);

    // Reverse direction
    set_motor_direction(1, 0);
    set_motor_direction(2, 0);
    set_motor_speed(1, 128);
    set_motor_speed(2, 128);

    sleep_ms(5000);

    // Stop motors
    set_motor_speed(1, 0);
    set_motor_speed(2, 0);

    return 0;
}
