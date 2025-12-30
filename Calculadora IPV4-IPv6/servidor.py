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
origem = (HOST, PORT)

tcp.bind(origem)

tcp.listen()
print('\nServidor TCP iniciado no IP', HOST, 'na porta', PORT)

try:
    while True:
        conexao, cliente = tcp.accept()
        print('\nConexão realizada por:', cliente)
        
        try:
            while True:
                msg1 = conexao.recv(1024)
                if not msg1:
                    break
                ipv6 = msg1.decode().strip()
                
                if ipv6.upper() == 'EXIT':
                    break
                
                msg2 = conexao.recv(1024)
                if not msg2:
                    break
                mask = msg2.decode().strip()
                mascara = int(mask.split('/')[1])
                
                if mask.upper() == 'EXIT':
                    break
                
                if (mascara < 49) or (mascara > 64):
                    print("Máscara inválida.")
                    break
                
                msg3 = conexao.recv(1024)
                if not msg3:
                    break
                quantRedes = msg3.decode().strip()
                
                if quantRedes.upper() == 'EXIT':
                    break
                
                print("Ipv6: " + ipv6)
                print("Mask: " + mask)
                print("Quantidade de Redes: " + quantRedes)
                
                subRedes = []
                intervalo = 65536 // pow(2, mascara - 48)
                quarteto = 0
                
                ipv6_base = ipv6[:15]
                for i in range(int(quantRedes)):
                    if quarteto < 65536:
                        subRedes.append(f"{ipv6_base}{hex(quarteto)[2:].zfill(4)}::")
                        quarteto += intervalo
                
                subRedes_str = "\n".join(subRedes)
                conexao.send(subRedes_str.encode())
        except Exception as e:
            print(f'Ocorreu um erro ao processar a conexão: {e}')
        finally:
            print('Finalizando conexão do cliente', cliente)
            conexao.close()
except Exception as e:
    print(f'Ocorreu um erro no servidor: {e}')
finally:
    tcp.close()
