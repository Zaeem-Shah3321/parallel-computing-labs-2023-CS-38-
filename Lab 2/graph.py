import matplotlib.pyplot as plt

# Number of processes
processes = [1, 2, 4, 8, 16]

# Measured execution times (seconds)
times = [0.000005 , 0.000048 , 0.002528 , 0.006776 , 0.002821]

# Calculate speedup
speedup = [times[0] / t for t in times]

# Ideal speedup (linear)
ideal_speedup = processes

plt.figure(figsize=(8,5))

# Measured Speedup with shaded area
plt.plot(
    processes, speedup, 
    'o-', 
    label='Measured Speedup', 
    color='#1f77b4', 
    linewidth=3, 
    markersize=10, 
    markerfacecolor='white', 
    markeredgewidth=2,
    markeredgecolor='#1f77b4'
)
plt.fill_between(processes, speedup, color='#1f77b4', alpha=0.8)

# Annotate measured points (blue) ABOVE the points with more gap
for x, y in zip(processes, speedup):
    plt.text(x, y + 0.40, f"{y:.6f}", ha='center', fontsize=8, fontweight='bold', color='#1f77b4')

# Ideal Speedup with shaded area
plt.plot(
    processes, ideal_speedup, 
    's--', 
    label='Ideal Speedup', 
    color='#ff7f0e', 
    linewidth=3, 
    markersize=10,
    markerfacecolor='white', 
    markeredgewidth=2,
    markeredgecolor='#ff7f0e'
)
plt.fill_between(processes, ideal_speedup, color='#ff7f0e', alpha=0.15)

# Annotate ideal points (orange) BELOW the points
#for x, y in zip(processes, ideal_speedup):
 #   plt.text(x, y - 0.55, f"{y:.0f}", ha='center', fontsize=12, fontweight='bold', color='#ff7f0e')

# Labels and title
plt.xlabel('Number of Processes', fontsize=14, fontweight='bold')
plt.ylabel('Speedup', fontsize=14, fontweight='bold')
plt.title('MPI Parallel Sum Program: Speedup vs Number of Processes', fontsize=14, fontweight='bold')

# Ticks
plt.xticks(processes, fontsize=12)
plt.yticks(range(0, 17, 1), fontsize=12)

# Grid and legend
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend(fontsize=12, shadow=True, facecolor='white')

plt.tight_layout()
plt.savefig('mpi_speedup_points_adjusted.png', dpi=300)
print("Graph saved as 'mpi_speedup_points_adjusted.png'")
plt.show()