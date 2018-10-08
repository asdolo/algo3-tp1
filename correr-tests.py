import os
import sys
import random
import math
from subprocess import Popen, PIPE, STDOUT

class color:
    PURPLE = '\033[95m'
    CYAN = '\033[96m'
    DARKCYAN = '\033[36m'
    BLUE = '\033[94m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    END = '\033[0m'

def clear_screen():
    print("\033[H\033[J")

def apply_effects(text, effects):
    res = ''
    for x in effects:
        res += x

    res += text

    for x in effects:
        res += color.END

    return res

def print_modo_de_uso():
    print(apply_effects('Modo de uso:', color.BOLD))
    print('  ' + 'python ' + os.path.basename(__file__) + ' [NRO. TEST]')
    print('')
    print(apply_effects('Tests:', color.BOLD))
    print('  ' + apply_effects('1, Fuerza Bruta vs Backtracking (sin podas)', color.GREEN))
    print('  ' + apply_effects('2, Fuerza Bruta vs Backtracking (con podas)', color.GREEN))
    print('')
    print(apply_effects('Ejemplo:', color.BOLD))
    print('  ' + 'python ' + os.path.basename(__file__) + ' 1')
    print('')

def check_compiled(algoritmo):
    try:
        p = Popen('./' + algoritmo, stdin=PIPE)
    except OSError:
        print('No se encuentra el ejecutable del algoritmo ' + algoritmo + '.')
        print('Por favor, compile el algoritmo usando ' + apply_effects('make ' + algoritmo, color.BOLD) + ' o simplemente ' + apply_effects('make', color.BOLD) + ' para compilar todos los algoritmos.')
        print('')
        exit()

    p.kill()

def get_output_name(num_test, algoritmo):
    return 'test-' + str(num_test) + '-' + algoritmo + '.csv'

def limpiar_outputs(num_test, algoritmo):
    output_file = open('output/' + get_output_name(num_test, algoritmo), 'w')
    output_file.write('n,V,resultado,tiempo' + '\n')
    output_file.close()


######################### MAIN #########################

clear_screen()

# Chequear si estamos en python 2
if sys.version_info[0] != 2:
    print(apply_effects('Por favor, ejecute este script en Python 2.', [color.RED, color.BOLD]))
    print('')
    exit()

# Chequear si los parametros son correctos
if len(sys.argv) != 2:
    print_modo_de_uso()
    exit()

parametro = sys.argv[1].lower()

# Chequear que los 3 algoritmos esten compilados
check_compiled('fuerzabruta')
check_compiled('backtracking')
check_compiled('programaciondinamica')

# Ejecutar test segun parametro
if parametro == '1':
    # Test 1:
    # Fuerza bruta vs backtracking (sin podas)

    # Limpio los outputs viejos del test
    limpiar_outputs(1, 'fuerzabruta')
    limpiar_outputs(1, 'backtracking')

    # El test se va a ejecutar con valores de n entre 1 y 20 (mas que eso no, ya que no tiene sentido porque fuerza bruta tarda mucho)
    # Para cada valor de n, los elementos del conjunto van a ser los numeros naturales de 1 a n,
    # y el valor V a calcular sera la suma de de todo S. Es decir, la suma de Gauss de 1 a n
    # Es decir, el unico subconjunto de S que sera solucion (y optima), sera S
    # Esto fuerza a que el algoritmo de Backtracking no haga ninguna poda por el orden en el que ejecuta las ramas de los sub-arboles
    # Por ejemplo, para n = 5, S = { 1, 2, 3, 4, 5 }, y V = (5*6)/2 = 15

    # El test en cuestion
    # Vario el tamano de n
    for n in range(1, 20 + 1):
        V = (n*(n+1))/2

        print('')
        print(' n=' + str(n) + '/' + str(20) + ', V = ' + str(V))

        # Genero los inputs que van a ir al stdin por un pipe
        input = str(n) + ' ' + str(V) + '\n'


        # Genero cada numero del conjunto
        for i in range(1, n + 1):
            input += str(i) + '\n'

        # Para reducir el error, voy a ejecutar los algoritmos 20 veces por cada valor de n
        for i in range(0, 20):
            p = Popen('./fuerzabruta ' + get_output_name(1, 'fuerzabruta'), stdin=PIPE, stdout=PIPE, shell=True)
            output = p.communicate(os.linesep.join([input]))[0]

        for i in range(0, 20):
            p = Popen('./backtracking ' + get_output_name(1, 'backtracking'), stdin=PIPE, stdout=PIPE, shell=True)
            output = p.communicate(os.linesep.join([input]))[0]
elif parametro == '2':
    # Test 2:
    # Fuerza bruta vs backtracking (con podas)

    # Limpio los outputs viejos del test
    limpiar_outputs(2, 'a-fuerzabruta')
    limpiar_outputs(2, 'a-backtracking')
    limpiar_outputs(2, 'b-fuerzabruta')
    limpiar_outputs(2, 'b-backtracking')
    limpiar_outputs(2, 'c-fuerzabruta')
    limpiar_outputs(2, 'c-backtracking')

# Parte a: Poda de medio arbol (tiempo exponencial reducido a la mitad)
    # El test en cuestion
    # Vario el tamano de n
    for n in range(1, 20 + 1):
        V = n

        print('')
        print(' n=' + str(n) + '/' + str(20) + ', V = ' + str(V))

        # Genero los inputs que van a ir al stdin por un pipe
        input = str(n) + ' ' + str(V) + '\n'

        # Genero cada numero del conjunto
        input += str(2*n) + '\n'
        for i in range(2, n + 1):
            input += str(1) + '\n'

        # Para reducir el error, voy a ejecutar los algoritmos 20 veces por cada valor de n
        for i in range(0, 20):
            p = Popen('./fuerzabruta ' + get_output_name(2, 'a-fuerzabruta'), stdin=PIPE, stdout=PIPE, shell=True)
            output = p.communicate(os.linesep.join([input]))[0]

        for i in range(0, 20):
            p = Popen('./backtracking ' + get_output_name(2, 'a-backtracking'), stdin=PIPE, stdout=PIPE, shell=True)
            output = p.communicate(os.linesep.join([input]))[0]

    # Parte b: Poda de todo el arbol (tiempo constante)  
    # El test en cuestion
    # Vario el tamano de n
    for n in range(1, 20 + 1):
        V = 0

        print('')
        print(' n=' + str(n) + '/' + str(20) + ', V = ' + str(V))

        # Genero los inputs que van a ir al stdin por un pipe
        input = str(n) + ' ' + str(V) + '\n'

        # Genero cada numero del conjunto
        for i in range(1, n + 1):
            input += str(i) + '\n'

        # Para reducir el error, voy a ejecutar los algoritmos 20 veces por cada valor de n
        for i in range(0, 20):
            p = Popen('./fuerzabruta ' + get_output_name(2, 'b-fuerzabruta'), stdin=PIPE, stdout=PIPE, shell=True)
            output = p.communicate(os.linesep.join([input]))[0]

        for i in range(0, 20):
            p = Popen('./backtracking ' + get_output_name(2, 'b-backtracking'), stdin=PIPE, stdout=PIPE, shell=True)
            output = p.communicate(os.linesep.join([input]))[0]

    # Parte c: Poda de todo el arbol menos una rama (tiempo lineal a n)    
    # El test en cuestion
    # Vario el tamano de n
    for n in range(1, 20 + 1):
        V = n

        print('')
        print(' n=' + str(n) + '/' + str(20) + ', V = ' + str(V))

        # Genero los inputs que van a ir al stdin por un pipe
        input = str(n) + ' ' + str(V) + '\n'

        # Genero cada numero del conjunto
        for i in range(1, n):
            input += str(1) + '\n'
        input += str(n) + '\n'

        # Para reducir el error, voy a ejecutar los algoritmos 20 veces por cada valor de n
        for i in range(0, 20):
            p = Popen('./fuerzabruta ' + get_output_name(2, 'c-fuerzabruta'), stdin=PIPE, stdout=PIPE, shell=True)
            output = p.communicate(os.linesep.join([input]))[0]

        for i in range(0, 20):
            p = Popen('./backtracking ' + get_output_name(2, 'c-backtracking'), stdin=PIPE, stdout=PIPE, shell=True)
            output = p.communicate(os.linesep.join([input]))[0]

elif parametro == '3':
    # Test 3:
    # Backtracking (con podas) vs Programacion Dinamica

    # Limpio los outputs viejos del test
    limpiar_outputs(3, 'backtracking')
    limpiar_outputs(3, 'programaciondinamica')

    # El test en cuestion
    # Vario el tamano de n
    for n in range(1, 20 + 1):
        V = int(10*math.pow(2,n))

        print(V)
        print('')
        print(' n=' + str(n) + '/' + str(20) + ', V = ' + str(V))

        # Genero los inputs que van a ir al stdin por un pipe
        input = str(n) + ' ' + str(V) + '\n'


        # Genero cada numero del conjunto
        for i in range(1, n):
            input += str(i) + '\n'
        input += str(V) + '\n'

        # Para reducir el error, voy a ejecutar los algoritmos 20 veces por cada valor de n
        for i in range(0, 20):
            p = Popen('./backtracking ' + get_output_name(3, 'backtracking'), stdin=PIPE, stdout=PIPE, shell=True)
            output = p.communicate(os.linesep.join([input]))[0]

        for i in range(0, 20):
            p = Popen('./programaciondinamica ' + get_output_name(3, 'programaciondinamica'), stdin=PIPE, stdout=PIPE, shell=True)
            output = p.communicate(os.linesep.join([input]))[0]

else:
    print_modo_de_uso()
    exit()    

print('Test finalizado!')
print('')
