import numpy as np
import math
import draw
import itertools

class Mesh:
    def __init__(self, faces, coordinates = None):
        self.faces = faces
        vertices = set(i for f in faces for i in f)
        self.n = max(vertices) + 1
        if coordinates != None:
            self.coordinates = np.array(coordinates)

        assert set(range(self.n)) == vertices
        for f in faces:
            assert len(f) == 3
        if coordinates != None:
            assert self.n == len(coordinates)
            for c in coordinates:
                assert len(c) == 3
        self.get_elements()
                
    def get_elements(self):
        self.opposite_vertices_for_edge = dict()
        for f in self.faces:
            for edge in itertools.combinations(f, 2):
                edge = tuple(sorted(edge))
                self.opposite_vertices_for_edge[edge] = set()

        for f in self.faces:
            for edge in itertools.combinations(f, 2):
                edge = tuple(sorted(edge))
                self.opposite_vertices_for_edge[edge].add(list(set(f).difference(set(edge)))[0]) 

        for f in self.faces:
            for edge in itertools.combinations(f, 2):
                edge = tuple(sorted(edge))
                self.opposite_vertices_for_edge[edge] = list(self.opposite_vertices_for_edge[edge])
                
        self.faces_for_vertex = [[] for i in range(self.n)]
        for idx, face in enumerate(self.faces):
            for v in face:
                self.faces_for_vertex[v].append(idx)
                
    @classmethod
    def fromobj(cls, filename):
        faces, vertices = draw.obj_read(filename)
        return cls(faces, vertices)

    def draw(self):
        draw.draw(self.faces, self.coordinates.tolist())

    def angleDefect(self, vertex): # vertex is an integer (vertex index from 0 to self.n-1)
        defect = 2 * np.pi
        for face in self.faces_for_vertex[vertex]:
            edge = self.faces[face]
            edge.remove(vertex)
            defect -= self.angle(self.coordinates[edge[0]] - self.coordinates[vertex],
                           self.coordinates[edge[1]] - self.coordinates[vertex])
        return defect    

    def angle(self, u, v):
        return np.arccos(np.dot(u, v) / (np.linalg.norm(u) * np.linalg.norm(v)))

    def buildLaplacianOperator(self, anchors=None, anchor_weight=1.0):
        weights, normed_weights = {}, {}
        sum_for_norm = np.zeros(self.n)
        if anchors is None:
            anchors = np.array([])
        for edge, opp in self.opposite_vertices_for_edge.items():
            weight = self.get_weights(edge, opp)
            sum_for_norm[edge[0]] += weight
            sum_for_norm[edge[1]] += weight
            weights[(edge[0], edge[1])], weights[(edge[1], edge[0])] = weight, weight
            
        for edge, weight in weights.items():
            normed_weights[edge] = weight / sum_for_norm[edge[0]]
            
        for idx in range(self.n):
            normed_weights[idx, idx] = -1
            
        row = self.n
        for anchor in anchors:
            normed_weights[(row, anchor)] = anchor_weight
            row += 1
            
        return normed_weights

    def get_weights(self, edge, opp):
        angle_1 = self.angle(self.coordinates[edge[0]] - self.coordinates[opp[0]], self.coordinates[edge[1]] - self.coordinates[opp[0]])
        angle_2 = self.angle(self.coordinates[edge[0]] - self.coordinates[opp[1]], self.coordinates[edge[1]] - self.coordinates[opp[1]])
        angles = np.array([angle_1, angle_2])
        weight = np.sum(1.0 / np.tan(angles))
        return weight

    def calculate_laplacian_value(self, laplacian, power=1.0):
        if isinstance(laplacian, dict):
            laplacian_value = np.zeros((self.n, 3))
            for edge, weight in laplacian.items():
                for col in range(3):
                    laplacian_value[edge[0]][col] += weight * power * self.coordinates[edge[1]][col]
            return laplacian_value

        else:
            return laplacian @ self.coordinates
   
    def transform(self, anchors, anchor_coordinates, anchor_weight = 1.):
        A = np.zeros((len(anchors) + self.n, self.n))
        laplacian = self.buildLaplacianOperator(anchors, anchor_weight)
        laplacian_matr = np.zeros((self.n, self.n))
        for coord, val in laplacian.items():
            A[coord[0]][coord[1]] = val
            if coord[0] < self.n:
                laplacian_matr[coord[0]][coord[1]] = val
        b = np.vstack((laplacian_matr @ self.coordinates, np.array(anchor_coordinates) * anchor_weight))
        self.coordinates = (np.linalg.inv(A.T @ A) @ A.T) @ b

    def smoothen(self, power=1.0):
        self.coordinates += self.calculate_laplacian_value(self.buildLaplacianOperator(), power)