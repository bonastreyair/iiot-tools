#define CORE0 0  // ESP32 first core
#define CORE1 1  // ESP32 second core
#define TASK_STACK_SIZE 10000  // in bytes
#define DEFAULT_PRIORITY 1  // 0 lower priority - 32 higher priority

// Parameters structure for FreeRTOS tasks
typedef struct {
  int delayTime = 1000;  // default value
  char id_example[10];  // max 10 characters, no default value
  float floatNum_example = 5.6;  // default value
} Parameters;

TaskHandle_t task1;
TaskHandle_t task2;

void setup() {
  Serial.begin(9600);
  Serial.println("\nsetup() running on core " + String(xPortGetCoreID()));

  // Create a task that will execute test1Task() function, with no parameters, with default priority on any core available core
  xTaskCreate(
    test1Task,        /* task function */
    "task1",          /* name of task */
    TASK_STACK_SIZE,  /* stack size of task */
    NULL,             /* no parameter for the task */
    DEFAULT_PRIORITY, /* sets the priority of the task */
    &task1);          /* task handle to keep track of created task */

  // Create a task that will execute test2Task() function, with parameters, with default priority and executed on core 0
  static Parameters task2_p;
  task2_p.delayTime = 2000;
  strcpy(task2_p.id_example, "test");
  xTaskCreatePinnedToCore(
    test2Task,        /* task function */
    "task2",          /* name of task */
    TASK_STACK_SIZE,  /* stack size of task */
    (void *) &task2_p,/* parameter of the task */
    DEFAULT_PRIORITY, /* sets the priority of the task */
    &task2,           /* task handle to keep track of created task */
    CORE0);           /* pin task to core 0 */
}

void loop() {
  static bool startup = true;
  
  if (startup) {
    Serial.println("loop() running on core " + String(xPortGetCoreID()));
    startup = false;
    
    // Delete task1 after 5 seconds
    delay(5000);
    vTaskDelete(task1);  // task1 is the defined handler
    Serial.println("task1 has been deleted");
  }
}

/* Additional functions */
void test1Task(void * pvParameters) {
  Serial.println("test1Task() running on core " + String(xPortGetCoreID()));

  for (;;) {
    Serial.println("task1 will be delayed for 1000 ms");
    delay(1000);
  }
}

void test2Task(void *pvParameters) {
  Parameters *params = (Parameters *) pvParameters;
  Serial.println("Parameters task2: " + String(params->delayTime) + ", " + String(params->id_example) + ", " + String(params->floatNum_example));
  Serial.println("test2Task() running on core " + String(xPortGetCoreID()));

  for (;;) {
    Serial.println("task2 will be delayed for " + String(params->delayTime) + " ms");
    delay(params->delayTime);
    params->delayTime = params->delayTime + 100;
  }
}
