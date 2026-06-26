def introduction_page():
    message = '''
        SAAESSC

        * Teste de conexão via bluetooth - 1
        * Adquirir dados - 2
        * Sair - 5
    '''

    print(message)
    command = input('Comando: ')

    return command