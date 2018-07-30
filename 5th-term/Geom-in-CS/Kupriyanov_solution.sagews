︠04f5bcab-2077-4e2b-93b8-b169f09a82a2s︠
%var u, v
x = (2+cos(u))*cos(v)
y = (2+cos(u))*sin(v)
z = sin(u)

r_u = vector([diff(x,u), diff(y,u), diff(z,u)])
r_v = vector([diff(x,v), diff(y,v), diff(z,v)])

r_uu = vector([diff(r_u[0],u), diff(r_u[1],u), diff(r_u[2],u)])
r_uv = vector([diff(r_u[0],v), diff(r_u[1],v), diff(r_u[2],v)])
r_vv = vector([diff(r_v[0],v), diff(r_v[1],v), diff(r_v[2],v)])

E = r_u.dot_product(r_u)
F = r_v.dot_product(r_u)
G = r_v.dot_product(r_v)

jacobian = sqrt(E * G - F * F)
L_matrix = matrix(3, 3, [r_uu[0], r_uu[1], r_uu[2], r_u[0], r_u[1], r_u[2], r_v[0], r_v[1], r_v[2]])
M_matrix = matrix(3, 3, [r_uv[0], r_uv[1], r_uv[2], r_u[0], r_u[1], r_u[2], r_v[0], r_v[1], r_v[2]])
N_matrix = matrix(3, 3, [r_vv[0], r_vv[1], r_vv[2], r_u[0], r_u[1], r_u[2], r_v[0], r_v[1], r_v[2]])

L = L_matrix.det() / jacobian
M = M_matrix.det() / jacobian
N = N_matrix.det() / jacobian

K = (N * L - M * M) / (E * G - F * F)
H = (E * N - 2 * M * F + L * G) / (2 * E * G - 2 * F * F)

# print(K.simplify_trig())
# print(H.simplify_trig())

D = H ^ 2 - 4 * K
x_1 = (H - sqrt(D)) / 2
x_2 = (H + sqrt(D)) / 2
f = min(x_1, x_2)
print(f.simplify_trig())
︡8f91a189-9692-4691-9af3-1287788c181c︡{"stdout":"-1/2*((cos(u)^2 + 4*cos(u) + 4)*sqrt(-(3*cos(u)^2 + 6*cos(u) - 1)/(cos(u)^2 + 4*cos(u) + 4)) - sqrt(cos(u)^2 + 4*cos(u) + 4)*(cos(u) + 1))/(cos(u)^2 + 4*cos(u) + 4)"}︡{"stdout":"\n"}︡{"done":true}︡









