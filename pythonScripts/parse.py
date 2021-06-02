
from datetime import datetime
import matplotlib.pyplot as plt

# get list of lines from a file 
def getLineseFromFile():
    file = open("TEST2.TXT" ,"r")
    lines = list()
    for i in file:
        lines.append(i)
    
    return lines

# parse data in lists: date/hour , pulse and SPO2 
def getParseDataInLists():
    lines = getLineseFromFile()
    list_of_date = list()
    list_of_pulse = list()
    list_of_SPO2 = list()

    for i in lines:
        elements = i.split(" ");
        date_time_str = elements[2] + ' ' + elements[0]
        date_time_obj = datetime.strptime(date_time_str, "%d.%m.%Y %H:%M:%S")
        list_of_date.append(date_time_obj)
        list_of_pulse.append(elements[3])
        list_of_SPO2.append(elements[4])
    
    lists = [list_of_date,list_of_pulse,list_of_SPO2]

    return lists


# plot graf by list 
def plotGraf(pltList1, pltList2,name,color):
    plt.plot(pltList1,pltList2, label=name,color = color)
    plt.ylabel('Valoare' + name)
    plt.xlabel('DateTime')
    plt.title('Grafic Puls over time' + name)
    plt.legend()
    plt.show()
    plt.savefig(name +'.svg')

if __name__ == '__main__':

    lists = getParseDataInLists()
    list1 = lists[1].copy()
    list2 = lists[2].copy()
    # convert string to int and float 
    list1 = [int(i) for i in lists[1]]
    list2 = [float(i) for i in lists[2]]

    # and plot graf 
    plotGraf( lists[0],list1, "Pulse","Red")
    plotGraf( lists[0],list2, "Spo2","Blue")

    # show all data in terminal
    print(lists)
