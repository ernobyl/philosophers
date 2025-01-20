# Philosophers
## About the project
  This project is an implementation of the dining philosophers problem using the pthreads library in C.
  Philosophers sit at a round table and do one of three things: eat, sleep, or think. While eating, they need two forks (one from their left and one from their right).
  The challenge is to avoid deadlock and make sure no philosopher starves.

  The main learning points of this project were how to create threads, and how to manage them with mutexes.
## Running the program
  ```
  ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: number_of_times_each_philosopher_must_eat]
  ```
  - number_of_philosophers: Number of philosophers and also the number of forks.
  - time_to_die: Time in milliseconds a philosopher waits after eating before dying of starvation.
  - time_to_eat: Time in milliseconds it takes a philosopher to eat.
  - time_to_sleep: Time in milliseconds a philosopher sleeps.
  - number_of_times_each_philosopher_must_eat: (Optional) If all philosophers eat at least this many times, the simulation will stop.
