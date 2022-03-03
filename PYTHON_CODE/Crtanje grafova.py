import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

plt.style.use('dark_background')


def animate(i):

    limiter = -24

    vrijednosti = pd.read_csv('data_test.csv')
    x = vrijednosti['x_vrijeme']
    vrijeme =x[limiter:]
    y1 = vrijednosti['y_senzor1']
    y11 = y1[limiter:]
    y2 = vrijednosti['y_senzor2']
    y22 = y2[limiter:]
    y3 = vrijednosti['y_senzor3']
    y33 = y3[limiter:]
    y4 = vrijednosti['y_senzor4']
    y44 = y4[limiter:]
    y5 = vrijednosti['y_senzor5']
    y55 = y5[limiter:]
    y6 = vrijednosti['y_senzor6']
    y66 = y6[limiter:]

    plt.subplot(321,facecolor='k')
    plt.cla()
    plt.plot(vrijeme,y11,'r',linewidth=5, label='Temperatura zraka [°C]')
    plt.grid()
    plt.ylim(0,50)
    plt.legend(loc='upper right')
    plt.xticks(rotation = 45)

    plt.subplot(322,facecolor='k')
    plt.cla()
    plt.plot(vrijeme,y22,'orange',linewidth=5, label='Temperatura tla [°C]')
    plt.grid()
    plt.ylim(0, 50)
    plt.legend(loc='upper right')
    plt.xticks(rotation=45)


    plt.subplot(323,facecolor='k')
    plt.cla()
    plt.plot(vrijeme, y33,'c',linewidth=5, label='Vlaga zraka [%]')
    plt.grid()
    plt.ylim(0, 100)
    plt.legend(loc='upper right')
    plt.xticks(rotation=45)



    plt.subplot(324,facecolor='k')
    plt.cla()
    plt.plot(vrijeme, y44,'b',linewidth=5, label='Vlaga tla [%]')
    plt.grid()
    plt.ylim(0, 100)
    plt.legend(loc='upper right')
    plt.xticks(rotation=45)


    plt.subplot(325,facecolor='k')
    plt.cla()
    plt.plot(vrijeme, y55,'w',linewidth=5, label='Tlak zraka [hPa]')
    plt.grid()
    plt.ylim(870, 1100)
    plt.legend(loc='upper right')
    plt.xticks(rotation=45)

    plt.subplot(326,facecolor='k')
    plt.cla()
    plt.plot(vrijeme, y66,'y',linewidth=5, label='Jačina sunca [%]')
    plt.grid()
    plt.ylim(0, 100)
    plt.legend(loc='upper right')
    plt.xticks(rotation=45)

    plt.tight_layout()


ani = FuncAnimation(plt.gcf(), animate)

plt.tight_layout()
plt.show()