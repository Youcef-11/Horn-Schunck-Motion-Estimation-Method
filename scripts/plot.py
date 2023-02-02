#!/usr/bin/env python
# Youcef CHORFI
import numpy as np
import matplotlib.pyplot as plt

if __name__=='__main__':
    u = np.genfromtxt("u.txt", delimiter=",")
    v = np.genfromtxt("v.txt", delimiter=",")
    u = np.reshape(u[~np.isnan(u)], (368,-1))
    v = np.reshape(v[~np.isnan(v)], (368,-1))
    img = plt.imread('../imgs/frame1.bmp')

    x = np.arange(u.shape[1])
    y = np.arange(u.shape[0])
    X, Y = np.meshgrid(x,y)
    print(X.shape, u.shape)
    plt.figure(figsize=(16,12))
    plt.imshow(img, cmap='gray')
    plt.streamplot(X, Y, v, -u, density = 0.5)
    plt.axis('off')
    plt.savefig('optical_flow.png')
    plt.show()
    