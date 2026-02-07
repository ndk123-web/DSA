import matplotlib.pyplot as plt

semesters = ["Sem 1", "Sem 2", "Sem 3", "Sem 4", "Sem 5"]

gpa = [9.55, 9.50, 9.20, 9.26, 9.26]
cgpa = [9.55, 9.53, 9.42, 9.38, 9.35]

plt.figure(figsize=(8,5))
plt.plot(semesters, gpa, marker='o', linewidth=2, label="Semester GPA")
plt.plot(semesters, cgpa, marker='s', linewidth=2, label="CGPA")

plt.title("College Name – Academic Performance Trend | Navnath Kadam")
plt.xlabel("Semester")
plt.ylabel("GPA")
plt.ylim(8.8,10)
plt.grid(alpha=0.3)
plt.legend()

plt.tight_layout()
plt.savefig("gpa_trend.png", dpi=300)
plt.show()
