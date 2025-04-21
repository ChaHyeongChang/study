import sqlite3
from tkinter import *


def save_to_db():
    # Entry에서 데이터 가져오기
    id_val = entry1.get()
    name_val = entry2.get()
    email_val = entry3.get()
    birth_year_val = entry4.get()

    # SQLite 연결
    con = sqlite3.connect(r"C:/Users/56flo/Desktop/testDB.db")
    cur = con.cursor()

    # 테이블 생성 (존재하지 않을 경우에만)
    cur.execute("""
    CREATE TABLE IF NOT EXISTS userTable (
        id CHAR(4),
        userName CHAR(10),
        email CHAR(15),
        birthYear INT
    )
    """)

    cur.execute("INSERT INTO userTable VALUES (?, ?, ?, ?)", (id_val, name_val, email_val, birth_year_val))
    # 변경사항 저장 및 연결 종료
    con.commit()
    con.close()

    # 입력 칸 초기화
    entry1.delete(0, END)
    entry2.delete(0, END)
    entry3.delete(0, END)
    entry4.delete(0, END)

    # 성공 메시지
    result_label_id.config(text="저장 완료")
    result_label_name.config(text="")
    result_label_email.config(text="")
    result_label_birth_year.config(text="")
    fetch_from_db()

def fetch_from_db():
    # SQLite 연결
    con = sqlite3.connect(r"C:/Users/56flo/Desktop/testDB.db")
    cur = con.cursor()

    # 데이터 조회
    cur.execute("SELECT * FROM userTable")
    rows = cur.fetchall()

    result_label_id.config(text="사용자ID\n-------------")
    result_label_name.config(text="사용자이름\n-------------")
    result_label_email.config(text="이메일\n-------------")
    result_label_birth_year.config(text="출생연도\n-------------")
    # 조회 결과 표시 (모든 데이터 출력)
    for row in rows:
        result_label_id.config(text=result_label_id.cget("text") + f"\n{row[0]}")
        result_label_name.config(text=result_label_name.cget("text") + f"\n{row[1]}")
        result_label_email.config(text=result_label_email.cget("text") + f"\n{row[0] + row[2]}")
        result_label_birth_year.config(text=result_label_birth_year.cget("text") + f"\n{row[3]}")

    # 연결 종료
    con.close()

# GUI 설정
window = Tk()
window.title("GUI 데이터 입력")
window.geometry("800x400")
window.resizable(False, False)

# 입력 칸과 버튼을 가로로 정렬
frame = Frame(window)
frame.pack(pady=10)

Label(frame).grid(row=0, column=0, padx=5)
entry1 = Entry(frame)
entry1.grid(row=0, column=1, padx=5)

Label(frame).grid(row=0, column=2, padx=5)
entry2 = Entry(frame)
entry2.grid(row=0, column=3, padx=5)

Label(frame).grid(row=0, column=4, padx=5)
entry3 = Entry(frame)
entry3.grid(row=0, column=5, padx=5)

Label(frame).grid(row=0, column=6, padx=5)
entry4 = Entry(frame)
entry4.grid(row=0, column=7, padx=5)

save_button = Button(frame, text="저장", command=save_to_db)
save_button.grid(row=0, column=8, padx=5)

fetch_button = Button(frame, text="조회", command=fetch_from_db)
fetch_button.grid(row=0, column=9, padx=5)

# 조회 결과를 표시할 Label
result_frame = Frame(window)
result_frame.pack(pady=20)

result_label_id = Label(result_frame, text="사용자ID\n-------------", anchor="nw", bg = "Yellow", width=25 , height = 50)
result_label_id.grid(row=0, column=0, padx=5)

result_label_name = Label(result_frame, text="사용자이름\n-------------", anchor="nw", bg = "Yellow",width=25, height = 50)
result_label_name.grid(row=0, column=1, padx=5)

result_label_email = Label(result_frame, text="이메일\n-------------", anchor="nw", bg = "Yellow",width=25, height = 50)
result_label_email.grid(row=0, column=2, padx=5)

result_label_birth_year = Label(result_frame, text="출생연도\n-------------", anchor="nw", bg = "Yellow", width=25, height = 50)
result_label_birth_year.grid(row=0, column=3, padx=5)

window.mainloop()