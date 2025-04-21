from tkinter import *
import sqlite3

def insertData():
    conn = sqlite3.connect("userDB.db")
    cur = conn.cursor()
    cur.execute("INSERT INTO userTable VALUES (?, ?, ?, ?)", 
                (edt1.get(), edt2.get(), edt3.get(), int(edt4.get())))
    conn.commit()
    conn.close()

    edt1.delete(0, END)
    edt2.delete(0, END)
    edt3.delete(0, END)
    edt4.delete(0, END)

def selectData():
    conn = sqlite3.connect("userDB.db")
    cur = conn.cursor()
    cur.execute("SELECT * FROM userTable")
    rows = cur.fetchall()
    conn.close()

    output.delete("1.0", END)
    output.insert(INSERT, "사용자ID\t이름\t이메일\t\t\t출생연도\n")
    output.insert(INSERT, "--------\t------\t-------------------------\t--------\n")
    for row in rows:
        output.insert(INSERT, f"{row[0]}\t{row[1]}\t{row[2]}\t{row[3]}\n")

# 윈도우 설정
window = Tk()
window.title("GUI 데이터 입력")
window.geometry("600x400")

# 입력 필드
edt1 = Entry(window, width=10)
edt2 = Entry(window, width=10)
edt3 = Entry(window, width=20)
edt4 = Entry(window, width=5)

edt1.grid(row=0, column=0, padx=5, pady=5)
edt2.grid(row=0, column=1, padx=5, pady=5)
edt3.grid(row=0, column=2, padx=5, pady=5)
edt4.grid(row=0, column=3, padx=5, pady=5)

# 버튼
btn1 = Button(window, text="입력", command=insertData)
btn2 = Button(window, text="조회", command=selectData)

btn1.grid(row=0, column=4)
btn2.grid(row=0, column=5)

# 출력 박스
output = Text(window, width=75, height=15, bg="yellow")
output.grid(row=1, column=0, columnspan=6, padx=10, pady=10)

window.mainloop()