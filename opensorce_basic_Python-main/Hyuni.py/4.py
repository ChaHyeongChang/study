'''
from tkinter import *

window = Tk()

window.title("윈도우 창 연습")
window.geometry("600x400")
window.resizable(width=FALSE, height=FALSE)\
    
label1 = Label(window, text = "oajsdo;fj;ak;fajfa;sdf")
button1 = Button(window, text = "파이썬 종료", fg = "red", command = quit)

label1.pack()
button1.pack()

window.mainloop()
'''


from tkinter import *

window = Tk()
window.title("체크버튼 & 라디오버튼")
window.geometry("400x300")

# ✅ 체크버튼 (여러 개 선택 가능)
chk_var1 = IntVar()   # 체크 상태 저장 변수 (0 or 1)
chk_var2 = IntVar()

chk1 = Checkbutton(window, text="사과", variable=chk_var1)
chk2 = Checkbutton(window, text="바나나", variable=chk_var2)

chk1.pack()
chk2.pack()

# ✅ 라디오버튼 (하나만 선택 가능)
radio_var = IntVar()  # 선택된 값 저장할 변수

rdo1 = Radiobutton(window, text="빨강", variable=radio_var, value=1)
rdo2 = Radiobutton(window, text="파랑", variable=radio_var, value=2)
rdo3 = Radiobutton(window, text="초록", variable=radio_var, value=3)

rdo1.pack()
rdo2.pack()
rdo3.pack()

window.mainloop()
