from tkinter import *

btnList = [""] * 4
fnameList = ["1. childhood_size_1500.gif", "2. youth_size_1500.gif", "3. manhood_size_1500.gif", "4. old_age_size_1500.gif"]
photoList=[None] * 4
i, k = 0, 0
xPos, yPos = 0, 0
num = 0

window = Tk()
window.title("The Voyage of Life, Thomas Cole, c. 1844-1848")
window.geometry("620x420")

for i in range(0, 4):
    photoList[i] = PhotoImage(file = "gif/" + fnameList[i])
    btnList[i] = Button(window, image = photoList[i])
    
for i in range(0, 2):
    for k in range(0, 2):
        btnList[num].place(x = xPos, y = yPos)
        num += 1
        xPos += 300
    xPos = 0
    yPos += 200

window.mainloop()