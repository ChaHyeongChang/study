from tkinter import *

index = 0
fnameList = [
    "1. childhood_size_1500.gif",
    "2. youth_size_1500.gif",
    "3. manhood_size_1500.gif",
    "4. old_age_size_1500.gif"
]
path = "C:/Users/56flo/Desktop/study/opensorce_basic_Python-main/Lecture 6/gif/"

window = Tk()
window.title("삶의 장면 보기")
window.geometry("1500x1000")

photo = PhotoImage(file=path + fnameList[index])
label1 = Label(window, image=photo)

def FuncFront():
    global index, photo
    index = (index + 1) % 4
    photo = PhotoImage(file=path + fnameList[index])
    label1.configure(image=photo)

def FuncBack():
    global index, photo
    index = (index - 1) % 4
    photo = PhotoImage(file=path + fnameList[index])
    label1.configure(image=photo)

# 버튼을 담을 프레임 생성
topFrame = Frame(window)
topFrame.pack(side="top", pady=10)

button1 = Button(topFrame, text="<< 이전", command=FuncBack)
button2 = Button(topFrame, text="다음 >>", command=FuncFront)
button1.pack(side="left", padx=30)
button2.pack(side="right", padx=30)

# 이미지 아래에 배치
label1.pack()

window.mainloop()
