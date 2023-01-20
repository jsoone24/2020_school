from multiprocessing import Pool
import os
import numpy as np
import pandas as pd
import time
import copy


def func(parameter):
    argument = parameter[0]
    tDict = parameter[1]
    tFriend = pd.DataFrame(columns=['Id', 'FNum', 'FFNum','FFNumAVG', "FFNLTFN", "FFNGTFN", "FFNEFN"])
    print('process id:', os.getpid())
    for id in argument:
        idFriendFNum = 0
        FFNLTFN = 0
        FFNGTFN = 0
        FFNEFN = 0
        for idFriend in tDict[id]:
            if idFriend in tDict.keys():
                idFriendFNum = idFriendFNum + len(tDict[idFriend])
                if (len(tDict[idFriend]) > len(tDict[id])):
                    FFNGTFN = FFNGTFN + 1
                elif (len(tDict[idFriend]) < len(tDict[id])):
                    FFNLTFN = FFNLTFN + 1
                else:
                    FFNEFN = FFNEFN + 1
        tFriend = tFriend.append(
        {'Id': id, 'FNum': len(tDict[id]), 'FFNum' : idFriendFNum, 'FFNumAVG': idFriendFNum / len(tDict[id]), "FFNLTFN": FFNLTFN,
         "FFNGTFN": FFNGTFN, "FFNEFN": FFNEFN}, ignore_index=True)
    return tFriend


if __name__ == '__main__':
    tDict = {}

    f = open("./facebook-links.txt", 'r')
    while True:
        templist = f.readline()
        if not templist:
            break
        else:
            templist = templist.split()
            if templist[0] not in tDict.keys():
                tDict[templist[0]] = [templist[1]]
            else:
                tDict[templist[0]].append(templist[1])
    f.close()

    for id in tDict.keys():
        templist = copy.deepcopy(tDict[id])
        for idFriend in templist:
            if idFriend not in tDict.keys():
                tDict[id].remove(idFriend)
            else:
                if id not in tDict[idFriend]:
                    tDict[id].remove(idFriend)

    templist = []
    for id in tDict.keys():
        if len(tDict[id]) == 0:
            templist.append(id)

    for id in templist:
        del (tDict[id])

    listlist = list(tDict.keys())

    multiprocessArr = []
    multiprocessResult = []

    start = time.time()  # 시작 시간 저장
    for i in range(0, len(listlist), 1000):
        if (len(listlist[i:]) < 1000):
            multiprocessArr.append([listlist[i:], tDict])
        else:
            multiprocessArr.append([listlist[i: i + 1000], tDict])

    with Pool(processes=4) as pool:
        multiprocessResult = pool.map(func, multiprocessArr)

    result_dataframe = pd.concat(multiprocessResult, ignore_index=True)

    print("time :", time.time() - start)  # 현재시각 - 시작시간 = 실행 시간

    print(result_dataframe)
    result_dataframe.to_csv('./facebook_bi_way.csv', sep='\t', na_rep='NaN', index=False)