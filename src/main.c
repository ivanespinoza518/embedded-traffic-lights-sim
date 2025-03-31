#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

const int LIGHT_TIMER = 10000 / portTICK_PERIOD_MS; // 10sec
const int TRANSITION_DELAY = 2000 / portTICK_PERIOD_MS; // 2sec

const gpio_num_t BUTTON = GPIO_NUM_0;

struct traffic_light {
    gpio_num_t red;
    gpio_num_t yellow;
    gpio_num_t green;
};

typedef struct traffic_light light;

void setup_button();
void setup_traffic_light(void *traffic_light);
void change_to_green(int green_light, int yellow_light, int red_light);
void change_to_red(int green_light, int yellow_light, int red_light);

void app_main() {
    setup_button();

    light north_south;
    north_south.red = GPIO_NUM_19;
    north_south.yellow = GPIO_NUM_18;
    north_south.green = GPIO_NUM_5;
    setup_traffic_light(&north_south);

    light east_west;
    east_west.red = GPIO_NUM_25;
    east_west.yellow = GPIO_NUM_26;
    east_west.green = GPIO_NUM_27;
    setup_traffic_light(&east_west);

    while (true) {
        change_to_green(north_south.green, north_south.yellow, north_south.red);
        change_to_red(north_south.green, north_south.yellow, north_south.red);

        change_to_green(east_west.green, east_west.yellow, east_west.red);
        change_to_red(east_west.green, east_west.yellow, east_west.red);
    }
}

void change_to_green(int green_light, int yellow_light, int red_light) {
    // Switch light from red to green
    gpio_set_level(red_light, 1);
    gpio_set_level(green_light, 0);

    // If button is not pressed, increase timer by 10 more seconds (total 20sec).
    // This is because we assume no one wants to cross the intersecting street.
    if (gpio_get_level(BUTTON)) {
        vTaskDelay(LIGHT_TIMER);
    }

    // Wait 10sec
    vTaskDelay(LIGHT_TIMER);
}

void change_to_red(int green, int yellow, int red) {
    // Switch light from green to yellow
    gpio_set_level(green, 1);
    gpio_set_level(yellow, 0);

    // Wait 2sec
    vTaskDelay(TRANSITION_DELAY);

    // Change from yellow to red
    gpio_set_level(yellow, 1);
    gpio_set_level(red, 0);

    // Wait 2sec
    vTaskDelay(TRANSITION_DELAY);
}

void setup_button() {
    // Input Button
    gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
}

void setup_traffic_light(void *traffic_light) {
    light *curr_light = (light *)traffic_light;

    // Set Lights to Output
    gpio_set_direction(curr_light->red, GPIO_MODE_OUTPUT); // Red
    gpio_set_direction(curr_light->yellow, GPIO_MODE_OUTPUT); // Yellow
    gpio_set_direction(curr_light->green, GPIO_MODE_OUTPUT); // Green

    // Red Initially (0 = on; 1 = off)
    gpio_set_level(curr_light->red, 0);
    gpio_set_level(curr_light->yellow, 1);
    gpio_set_level(curr_light->green, 1);
}
