# примеры проверок (сначала запускаете ячейку с классом, потом с проверкой):


sphere = Variety([(3,2,1), (2,3,0), (1,0,3),(0,1,2)])
torus = Variety([
        (1,0,3),
        (1,3,2),
        (2,3,6),
        (3,4,6),
        (4,0,6),
        (1,6,0),
        (2,6,5),
        (1,5,6),
        (2,5,0),
        (3,0,5),
        (5,4,3),
        (1,4,5),
        (1,2,4),
        (2,0,4),
    ])

def test1():
    assert sphere.check() == True
    assert torus.check() == True
    assert Variety([(1,2,3), (2,3,0), (3,0,1),(0,1,2)]).check() == False
    assert Variety([(1,2,3), (2,3,1), (3,0,1),(0,1,2)]).check() == False
    assert Variety([(1,2,0), (1,0,2)]).check() == False
    assert Variety([(3,2,1), (2,3,0), (1,0,3),(0,1,2), (6,5,4), (5,6,0), (4,0,6),(0,4,5)]).check() == False


def test2():
    assert sphere.Euler() == 2
    assert torus.Euler() == 0

def test3():
    assert sphere.d_0(lambda x : x)(1, 2) == 1
    assert torus.d_0(lambda x : x**2)(4, 3) == -7

def test4():
    assert sphere.check_form(2, lambda x,y,z : x+y+z if (x-y)*(y-z)*(z-x)>0 else -(x+y+z)) == True
    assert torus.check_form(1,lambda v,w : 1) == False

def test5():
    assert sphere.d_1(lambda x, y : x-y)(0, 1, 2) == 0
    assert sphere.d_1(lambda x, y : x*y if x<y else -x*y)(1, 2, 3) == 5

def test61():
    assert sphere.wedge(0,0, lambda x: x, lambda x: -x)(2) == -4

def test62():
    assert sphere.wedge(0,1, lambda x: x, lambda x,y: y-x)(2,3) == 5/2

def test63():
    assert sphere.wedge(0,2, lambda x: x, lambda x,y,z:  x+y+z if (x-y)*(y-z)*(z-x)>0 else -(x+y+z) )(0,1,2) == 3

def test64():
    assert sphere.wedge(1,1, lambda x,y: x-y, lambda x,y: y-x)(1,2,3) == 0

tests = [(1, test1),
         (2, test2),
         (3, test3),
         (4, test4),
         (5, test5),
         ("6.1", test61),
         ("6.2", test62),
         ("6.3", test63),
         ("6.4", test64),
        ]

for i, t in tests:
    try:
        t()
    except:
        print('Функция задания {0} не прошла проверку'.format(i))
    else:
        print('Ошибок в задании {} не найдено'.format(i))

