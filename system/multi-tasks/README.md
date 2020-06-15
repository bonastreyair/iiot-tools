# System
## Multi Tasks
This example explains the common usage of tasks with the ESP32 thanks to [FreeRTOS](https://www.freertos.org/).

It tries to resolve many common questions:
 - How to start a task?
 - How to start a task with a specific core?
 - How to use a `struct` for parameters when starting a task?
 - How to set a specific priority for a task?
 - How to delete a task?

[[Go back]](/system)

### Hardware
- ESP32

### [Code](multi-tasks.ino)
```cpp
#define CORE0 0  // ESP32 first core
#define CORE1 1  // ESP32 second core
#define TASK_STACK_SIZE 10000  // in bytes
#define DEFAULT_PRIORITY 1  // 0 lower priority - 32 higher priority
#define FREERTOS_SYSTEM_TASKS 7  // number of tasks needed to FreeRTOS system to work

// Parameters example structure for FreeRTOS tasks
typedef struct {
  int delayTime = 1000;  // default value
  char id_example[10];  // max 10 characters, no default value
  float floatNum_example = 5.628;  // default value
} Parameters;

TaskHandle_t xTasksManager = NULL, xTask1 = NULL, xTask2 = NULL;

void setup() {
  Serial.begin(9600);
  Serial.println("\nBooting device...");
  LOG("setup() running on core " + String(xPortGetCoreID()));

  // Create a task that will execute tasksManager() function, with no parameters, with default priority on any available core
  xTaskCreate(
    tasksManager,     /* task function */
    "tasksManager",   /* name of task */
    TASK_STACK_SIZE,  /* stack size of task */
    NULL,             /* no parameter for the task */
    DEFAULT_PRIORITY, /* sets the priority of the task */
    &xTasksManager);  /* task handle to keep track of created task */
}

void loop() {
  LOG(String(uxTaskGetNumberOfTasks()-FREERTOS_SYSTEM_TASKS) + " running tasks");
  delay(1000);
}

/* Additional functions */
void tasksManager(void * pvParameters) {
  LOG("running on core " + String(xPortGetCoreID()));
  // Create a task that will execute test1Task() function, with no parameters, with default priority on any available core
  xTaskCreate(
    test1Task,            /* task function */
    "task1",              /* name of task */
    TASK_STACK_SIZE,      /* stack size of task */
    NULL,                 /* no parameter for the task */
    DEFAULT_PRIORITY,     /* sets the priority of the task */
    &xTask1);             /* task handle to keep track of created task */
  ulTaskNotifyTake(pdTRUE, portMAX_DELAY);  // Waits until task is ready

  // Create a task that will execute test2Task() function, with parameters, with default priority and executed on core 0
  Parameters xTask2Params;
  xTask2Params.delayTime = 2000;
  strcpy(xTask2Params.id_example, "test");
  xTaskCreatePinnedToCore(
    test2Task,             /* task function */
    "task2",               /* name of task */
    TASK_STACK_SIZE,       /* stack size of task */
    (void*) &xTask2Params, /* parameter of the task */
    DEFAULT_PRIORITY,      /* sets the priority of the task */
    &xTask2,               /* task handle to keep track of created task */
    CORE1);                /* pin task to core 1 */
  ulTaskNotifyTake(pdTRUE, portMAX_DELAY);  // Waits until task is ready
   
  // Notify tasks to start simultaneously
  xTaskNotifyGive(xTask1);
  xTaskNotifyGive(xTask2);

  // Delete task1 after 6 seconds
  LOG("deleting task1 after 6 seconds");
  vTaskDelay(6000 / portTICK_PERIOD_MS);  // Blocks the task and lets other tasks to work
  vTaskDelete(xTask1);  // task1 is the defined handler kills the task and frees up memory space
  LOG("deleted " + String(pcTaskGetTaskName(xTask1)));

  vTaskDelay(3000 / portTICK_PERIOD_MS);
  LOG("autodestroyed");
  vTaskDelete(NULL);  // Kills itself and frees up memory space
}

void test1Task(void * pvParameters) {
  xTaskNotifyGive(xTasksManager);
  ulTaskNotifyTake(pdTRUE, portMAX_DELAY);  // Blocks indefinitely until it receives a notification
  LOG("running on core " + String(xPortGetCoreID()));

  for (;;) {
    LOG("delayed using 'vTaskDelay()' for 1000 ms");
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // Blocks the task and lets other tasks to work
  }
  LOG("autodestroyed");
  vTaskDelete(NULL);  // Kills itself and frees up memory space
}

void test2Task(void *pvParameters) {
  Parameters params = *(Parameters *) pvParameters;  // Copy parameters
  xTaskNotifyGive(xTasksManager);
  ulTaskNotifyTake(pdTRUE, portMAX_DELAY);  // Blocks indefinitely until it receives a notification
  LOG("running on core " + String(xPortGetCoreID()));
  
  LOG("parameters: " + String(params.delayTime) + ", " + String(params.id_example) + ", " + String(params.floatNum_example));
  for (;;) {
    LOG("delayed using 'vTaskDelay()' for " + String(params.delayTime) + " ms");
    vTaskDelay(params.delayTime / portTICK_PERIOD_MS);  // Blocks the task and lets other tasks to work
    params.delayTime += 100;
    if (params.delayTime > 2500) {
      break;
    }
  }
  LOG("autodestroyed");
  vTaskDelete(NULL);  // Kills itself and frees up memory space
}

void LOG(StringSumHelper message) {
  char *taskName = pcTaskGetTaskName(NULL);
  Serial.flush();
  Serial.println(String(taskName) +" -> " + message);
}
```

### Libraries
- [_Standard ESP32 Library_](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos.html) by Espressif - Installed with ESP32 Board in Arduino IDE

  Library which includes a tuned FreeRTOS designed for ESP32

[[Go back]](/system)
