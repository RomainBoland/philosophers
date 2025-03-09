# Philosophers

## 📝 Description

This project is an implementation of the classic "Dining Philosophers Problem" - a simulation that illustrates synchronization issues in concurrent programming and techniques to solve them. The problem consists of philosophers sitting at a round table with a bowl of spaghetti in the middle, where each philosopher needs two forks to eat but there's only one fork between each pair of philosophers.

In this implementation:
- Each philosopher is a thread
- Each fork is protected by a mutex
- Philosophers alternate between eating, sleeping, and thinking
- If a philosopher doesn't eat within a specified time, they die

## 🛠️ Requirements

- GCC compiler
- Make
- POSIX threads library (pthread)
- Unix-based operating system (Linux/macOS)

## 🔧 Installation

Clone the repository and compile the program:

```bash
git clone git@github.com:RomainBoland/philosophers.git
cd philosophers
cd philo
make
```

This will create the executable `philo`.

## 💻 Usage

Run the program with the following parameters:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

Where:
- `number_of_philosophers`: The number of philosophers and also the number of forks.
- `time_to_die`: Time in milliseconds after which a philosopher dies if they haven't started eating.
- `time_to_eat`: Time in milliseconds it takes for a philosopher to eat.
- `time_to_sleep`: Time in milliseconds a philosopher will spend sleeping.
- `number_of_times_each_philosopher_must_eat` (optional): If specified, the simulation stops after all philosophers have eaten at least this many times.

### Example

```bash
./philo 5 800 200 200
```

This creates a simulation with 5 philosophers, where each philosopher:
- Dies if they don't start eating within 800ms of their last meal
- Takes 200ms to eat
- Spends 200ms sleeping

## 🎮 How It Works

1. **Initialization**:
   - Each philosopher is assigned a unique ID
   - Each fork is protected by a mutex
   - Each philosopher needs the forks to their left and right to eat

2. **Philosopher Lifecycle**:
   - Thinking: Philosopher is waiting to eat
   - Eating: Philosopher has both forks and is eating
   - Sleeping: Philosopher has finished eating and is sleeping

3. **Termination Conditions**:
   - A philosopher dies (hasn't eaten within `time_to_die` milliseconds)
   - All philosophers have eaten at least `number_of_times_each_philosopher_must_eat` times (if specified)

4. **Deadlock Prevention**:
   - Philosophers with even IDs take their right fork first, odd IDs take their left fork first
   - This asymmetry prevents the circular waiting condition that leads to deadlock

## 🐛 Known Issues and Limitations

- With very extreme parameters (very short time_to_die), reporting might be slightly delayed
- With very large numbers of philosophers, system resource limits might be reached

## 🧪 Testing

You can test the program with different parameters to observe various scenarios:

1. **Normal Operation**:
   ```
   ./philo 5 800 200 200
   ```

2. **Death Scenario**:
   ```
   ./philo 4 310 200 100
   ```

3. **Limited Meals**:
   ```
   ./philo 5 800 200 200 7
   ```

4. **Edge Case - One Philosopher**:
   ```
   ./philo 1 800 200 200
   ```

## 📚 Technical Implementation

- **Threads**: Each philosopher is a separate POSIX thread
- **Mutexes**: Used to protect forks and shared state
- **Timing**: Uses `gettimeofday()` for microsecond precision
- **Monitoring**: A separate thread monitors for death conditions

## 👥 Authors

- [Your Name]
