/*
Реализуйте класс TeamTasks, позволяющий хранить статистику
по статусам задач команды разработчиков.


Метод PerformPersonTasks должен реализовывать следующий алгоритм:

	1. Рассмотрим все невыполненные задачи разработчика person;
	2. Упорядочим их по статусам: сначала все задачи в статусе NEW,
	затем все задачи в статусе IN_PROGRESS и, наконец, задачи в
	статусе TESTING;
	3. Рассмотрим первые task_count задач и переведём каждую из них
	в следующий статус в соответствии с естественным порядком:
	NEW → IN_PROGRESS → TESTING → DONE;
	4. Вернём кортеж из двух элементов: информацию о статусах обновившихся
	задач (включая те, которые оказались в статусе DONE) и информацию о
	статусах остальных не выполненных задач.


В случае отсутствия разработчика с именем person метод PerformPersonTasks
должен вернуть кортеж из двух пустых TasksInfo.


Гарантируется, что task_count является положительным числом. Если task_count
превышает текущее количество невыполненных задач разработчика, достаточно
считать, что task_count равен количеству невыполненных задач: дважды обновлять
статус какой-либо задачи в этом случае не нужно.


Кроме того, гарантируется, что метод GetPersonTasksInfo не будет вызван для
разработчика, не имеющего задач.


Пример работы метода PerformPersonTasks.
Предположим, что у конкретного разработчика имеется 10 задач со следующими статусами:
	► NEW — 3
	► IN_PROGRESS — 2
	► TESTING — 4
	► DONE — 1


Поступает команда PerformPersonTasks с параметром task_count = 4, что означает обновление
статуса для 3 задач c NEW до IN_PROGRESS и для 1 задачи с IN_PROGRESS до TESTING.
Если выписать статусы всех задач по порядку, а обновляемые заключить в квадратные скобки,
то изменение можно изобразить следующим образом:

  [NEW, NEW, NEW, IN_PROGRESS,] IN_PROGRESS, TESTING, TESTING, TESTING, TESTING, DONE

  ==>

  [IN_PROGRESS, IN_PROGRESS, IN_PROGRESS, TESTING,] IN_PROGRESS, TESTING, TESTING, TESTING,
  TESTING, DONE


Таким образом, новые статусы задач будут следующими:
	► IN_PROGRESS — 3 обновлённых, 1 старая
	► TESTING — 1 обновлённая, 4 старых
	► DONE — 1 старая

В этом случае необходимо вернуть кортеж из 2 словарей:
	► Обновлённые задачи: IN_PROGRESS — 3, TESTING — 1.
	► Необновлённые задачи, исключая выполненные: IN_PROGRESS — 1, TESTING — 4.

Ни один из словарей не должен содержать лишних элементов, то есть статусов, которым
соответствует ноль задач.

По условию, DONE задачи не нужно возвращать в необновлённых задачах (untouched_tasks).
*/


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
using namespace std;


// Перечислимый тип для статуса задачи
enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};


// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;


// Апгрейд статуса задачи
TaskStatus Next(const TaskStatus& status){
	return static_cast<TaskStatus>(static_cast<int>(status) + 1);
}


// Очистка от статусов, которые не имеют текущих задач
void RemoveZeros (TasksInfo& tasks){
	for (TaskStatus status = TaskStatus::NEW;
		status != TaskStatus::DONE; status = Next(status)){
		vector<TaskStatus> statuse_to_remove;
		for (const auto& task_item : tasks){
			if (task_item.second == 0){
				statuse_to_remove.push_back(task_item.first);
			}
		}
		for (const TaskStatus status : statuse_to_remove) {
			tasks.erase(status);
		}
	}
}


class TeamTasks {
public:
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) const;

  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string& person);

  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
      const string& person, int task_count);

private:
  map<string, TasksInfo> person_task_;
};



const TasksInfo& TeamTasks::GetPersonTasksInfo(const string& person) const {
	return TeamTasks::person_task_.at(person);
}

void TeamTasks::AddNewTask(const string& person){
	++person_task_[person][TaskStatus::NEW];
}


tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(
		const string& person, int task_count) {
	TasksInfo updated_tasks, untouched_tasks;

	TasksInfo& tasks = person_task_[person];

	for (TaskStatus status = TaskStatus::NEW;
			status != TaskStatus::DONE;
		status = Next(status)){
		updated_tasks[Next(status)] = min(task_count, tasks[status]);
		task_count -= updated_tasks[Next(status)];
	}

	for (TaskStatus status = TaskStatus::NEW;
			status != TaskStatus::DONE;
			status = Next(status)){
		untouched_tasks[status] = tasks[status] - updated_tasks[Next(status)];
		tasks[status] += updated_tasks[status] - updated_tasks[Next(status)];
	}
	tasks[TaskStatus::DONE] += updated_tasks[TaskStatus::DONE];

	RemoveZeros(updated_tasks);
	RemoveZeros(untouched_tasks);
	RemoveZeros(person_task_.at(person));

	return {updated_tasks, untouched_tasks};
}


void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}


int main() {
  TeamTasks tasks;
  tasks.AddNewTask("Ilia");
  for (int i = 0; i < 3; ++i) {
    tasks.AddNewTask("Ivan");
  }
  cout << "Ilia's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

  TasksInfo updated_tasks, untouched_tasks;

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  return 0;
}
