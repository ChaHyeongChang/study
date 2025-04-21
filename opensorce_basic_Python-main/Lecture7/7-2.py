import matplotlib.pyplot as plt
import csv

# 한글 폰트 설정 (Windows용)
plt.rcParams['font.family'] = 'Malgun Gothic'
plt.rcParams['axes.unicode_minus'] = False


file_path = r"C:\Users\56flo\Desktop\data\SURFACE_ASOS_131_DAY_2003_2003_2018.csv"

# 데이터 초기화
x_data = []
avg_temp = []
min_temp = []
max_temp = []

day = 1


with open(file_path, 'r', encoding='cp949') as f:
    reader = csv.reader(f)
    header = next(reader)  # 첫 줄(열 제목) 건너뛰기

    for row in reader:
        try:
            if row[2] and row[3] and row[5]:  # 평균, 최저, 최고 기온이 있는지 확인
                avg_temp.append(float(row[2]))
                min_temp.append(float(row[3]))
                max_temp.append(float(row[5]))
                x_data.append(day)
                day += 1
        except ValueError:
            continue

print(f"데이터 개수: {len(x_data)}")  # 데이터 개수 확인


plt.figure(figsize=(12, 6))
plt.plot(x_data, max_temp, color='red', label='최고기온', linewidth=1)
plt.plot(x_data, avg_temp, color='orange', label='평균기온', linewidth=1)
plt.plot(x_data, min_temp, color='blue', label='최저기온', linewidth=1)

plt.title("서울시 2003년도 기온 변화")
plt.xlabel("일자 (1일 ~ 365일)")
plt.ylabel("기온 (°C)")

# Y축 눈금 -10 ~ 40 사이로 지정
plt.yticks(range(-10, 41, 10))

plt.legend(loc='upper right')
plt.grid(True)
plt.tight_layout()
plt.show()
