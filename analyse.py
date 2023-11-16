import sys
import re
import numpy as np
import matplotlib.pyplot as plt
import matplotlib
matplotlib.use('GTK3Cairo')
import matplotlib.patches as mpatches

COLOURS = ['tab:blue', 'tab:orange', 'tab:green', 'tab:red', 'tab:purple', 'tab:brown', 'tab:pink', 'tab:gray', 'tab:olive', 'tab:cyan']

plt_y = []
plt_w = []
plt_x = []
plt_c = []

# parse the data
pids = dict()
run_info = dict()
start_time = None

wait_time_samples = []
run_time_samples = []

for line in open(sys.argv[1], 'rb'):
    if line.startswith(b'$$'):
        # parse the line
        m = re.search(b'timeslice summary for pid ([0-9]+) \\((.*)\\) : queued at ([0-9]+), ran at ([0-9]+), ended at ([0-9]+)', line)
        pid, proc, wake, run, end = int(m[1]), m[2], int(m[3]), int(m[4]), int(m[5])
        pids[pid] = proc.decode()
        if pid not in run_info:
            run_info[pid] = []

        # get a start time
        if start_time is None:
            start_time = wake

        wake -= start_time
        run  -= start_time
        end  -= start_time

        run_info[pid].append((wake/1000, run/1000, end/1000))
        waiting_time = run - wake
        running_time = end - run

        # Calculate CPU starvation time

        # do something interesting with these figures
        wait_time_samples.append(waiting_time / 1000)
        run_time_samples.append(running_time / 1000)
        plt_x.append(run / 1000)
        plt_w.append(running_time / 1000)
        plt_y.append(1)
        try:
            plt_c.append(COLOURS[pid - 1])
        except IndexError:
            random_color = np.random.choice(COLOURS)
            plt_c.append(random_color)


# Calculate the total waiting time
total_running_time = sum(run_time_samples)

# Calculate the total duration of the timeline
total_duration = plt_x[-1] + plt_w[-1]

t_times = []
r_times = []
for pid, info in run_info.items():
    t_times.append(info[-1][2] - info[0][0])
    r_times.append(info[0][1] - info[0][0])

# Calculate the total waiting time
total_running_time = sum(run_time_samples)

# Calculate the total duration of the timeline
total_duration = plt_x[-1] + plt_w[-1]

# Calculate the CPU downtime
cpu_downtime = total_duration - (total_running_time)

cpu_utilization = (100 - (cpu_downtime/total_duration) * 100)

throughput = (len(pids) / total_duration) * 60000

bar_colors = [COLOURS[pid - 1] for pid in pids.keys()]

# Mean data
print(f'Mean wait time: {(sum(wait_time_samples) / len(wait_time_samples)):.02f}ms')

print(f'CPU utilization: {cpu_utilization:.02f}%')

print(f"Throughput {throughput:.02f} proccess/min")

mean_t_time = (sum(t_times) / len(pids)) / 10000

print(f"Mean Turnaround Time: {mean_t_time:.02f}s")

mean_r_time = sum(r_times) / len(pids)

print(f"Mean Response Time: {mean_r_time:.02f}ms")



# complete the plot
# Legend
patches = []
for i, c in enumerate(COLOURS):
    if i + 1 in pids:
        l = pids[i + 1]
        patches.append(mpatches.Patch(color=c, label=l))
plt.legend(handles=patches)

# plot bars
plt.barh(y=plt_y, width=plt_w, left=plt_x, color=plt_c)
plt.yticks([])
plt.tight_layout()
plt.xlabel("Time (ms)")
plt.title("Proccess Execution Timeline")
plt.show()

# Plot showing response time for each process
plt.figure(figsize=(10, 5))
plt.bar(list(run_info.keys()), r_times, color=bar_colors )
plt.xlabel('Process ID')
plt.ylabel('Response Time(ms)')
plt.title('Response Times for Each Process')
plt.ylim(0, total_duration)
plt.legend(handles=patches)
plt.show()

# Plot showing CPU turnaround time for each process
plt.figure(figsize=(10, 5))
plt.bar(list(run_info.keys()), t_times, color=bar_colors)
plt.xlabel('Process ID')
plt.ylabel('Turnaround Time(ms)')
plt.title('Turnaround Times for Each Process')
plt.ylim(0, total_duration)
plt.legend(handles=patches)
plt.show()

