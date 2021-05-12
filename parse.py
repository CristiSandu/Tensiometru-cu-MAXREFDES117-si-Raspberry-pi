
from datetime import datetime
import matplotlib.pyplot as plt

def getLineseFromFile():
    file = open("TEST.TXT" ,"r")
    lines = list()
    for i in file:
        lines.append(i)
    
    return lines

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

if __name__ == '__main__':
    lists = getParseDataInLists()
    plt.plot(lists[0], lists[1], label="Puls")
    plt.plot(lists[0], lists[2], label="SPO2")
    plt.ylabel('Valoare Puls/SPO2')
    plt.xlabel('DateTime')
    plt.title('Grafic Puls over time')
    # plt.ylim(top=40)
    plt.legend()
    plt.show()
    print(lists)
