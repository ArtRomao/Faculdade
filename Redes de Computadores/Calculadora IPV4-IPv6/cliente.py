###########################################################################
###                                                                     ###
###                    Calculadora IPv6 de sub-rede                     ###
###                                                                     ###
###                  Arthur Romão Barreto | RA: 2474050                 ###
###               Antonio Teixeira Baptista | RA: 2459574               ###
###                                                                     ###
###########################################################################

import socket

HOST = '127.0.0.1'
PORT = 5000
tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
destino = (HOST, PORT)

try:
    tcp.connect(destino)
    print('Para sair digite EXIT a qualquer momento.\n')

    while True:
        ipv6 = input("Insira o ipv6(/48): ")
        if ipv6.upper() == 'EXIT':
            break
        tcp.send(ipv6.encode())
        
        mask = input("Insira a máscara: ")
        if mask.upper() == 'EXIT':
            break
        tcp.send(mask.encode())
        
        quantRedes = input("Insira a quantidade de redes: ")
        if quantRedes.upper() == 'EXIT':
            break
        tcp.send(quantRedes.encode())
        
        subRedes = tcp.recv(22*65536).decode().split('\n')
        cont = 1
        for i in subRedes:
            print("REDE: " + str(cont))
            print(i)
            cont += 1
            

finally:
    tcp.close()
