from __future__ import division
import numpy as np
from numpy import arctan2, fliplr, flipud


def gradient(image, same_size=False):
    sy, sx = image.shape
    if same_size:
        gx = np.zeros(image.shape)
        gx[:, 1:-1] = -image[:, :-2] + image[:, 2:]
        gx[:, 0] = -image[:, 0] + image[:, 1]
        gx[:, -1] = -image[:, -2] + image[:, -1]
    
        gy = np.zeros(image.shape)
        gy[1:-1, :] = image[:-2, :] - image[2:, :]
        gy[0, :] = image[0, :] - image[1, :]
        gy[-1, :] = image[-2, :] - image[-1, :]
    
    else:
        gx = np.zeros((sy-2, sx-2))
        gx[:, :] = -image[1:-1, :-2] + image[1:-1, 2:]

        gy = np.zeros((sy-2, sx-2))
        gy[:, :] = image[:-2, 1:-1] - image[2:, 1:-1]
    
    return gx, gy
т

def magnitude_orientation(gx, gy):
    magnitude = np.sqrt(gx**2 + gy**2)
    orientation = (arctan2(gy, gx) * 180 / np.pi) % 360
            
    return magnitude, orientation


def compute_coefs(csx, csy, dx, dy, n_cells_x, n_cells_y):if csx != csy:
    else: # Squared cells
        # Note: in this case, dx = dy, we differentiate them only to make the code clearer
        
        # We want a squared coefficients matrix so that it can be rotated to interpolate in every direction
        n_cells = max(n_cells_x, n_cells_y)
        
        # Every cell of this matrix corresponds to (x - x_1)/dx 
        x = (np.arange(dx)+0.5)/csx
        
        # Every cell of this matrix corresponds to (y - y_1)/dy
        y = (np.arange(dy)+0.5)/csy
        
        y = y[np.newaxis, :]
        x = x[:, np.newaxis]

        # CENTRAL COEFFICIENT
        ccoefs = np.zeros((csy, csx))

        ccoefs[:dy, :dx] = (1 - x)*(1 - y)
        ccoefs[:dy, -dx:] = fliplr(y)*(1 - x)
        ccoefs[-dy:, :dx] = (1 - y)*flipud(x)
        ccoefs[-dy:, -dx:] = fliplr(y)*flipud(x)

        coefs = np.zeros((csx*n_cells - dx, csy*n_cells - dy))
        coefs[:-dy, :-dx] = np.tile(ccoefs, (n_cells - 1, n_cells - 1))

        # REST OF THE BORDER
        coefs[:-dy, -dx:] = np.tile(np.concatenate(((1 - x), np.flipud(x))), (n_cells - 1, dy))
        coefs[-dy:, :-dx] = np.tile(np.concatenate(((1 - y), np.fliplr(y)), axis=1), (dx, n_cells - 1))
        coefs[-dy:, -dx:] = 1

        return coefs


def interpolate_orientation(orientation, sx, sy, nbins, signed_orientation):
    if signed_orientation:
        max_angle = 360
    else:
        max_angle = 180
    
    b_step = max_angle/nbins
    b0 = (orientation % max_angle) // b_step
    b0[np.where(b0>=nbins)]=0
    b1 = b0 + 1
    b1[np.where(b1>=nbins)]=0
    b = np.abs(orientation % b_step) / b_step
    
    temp_coefs = np.zeros((sy, sx, nbins))
    for i in range(nbins):
        temp_coefs[:, :, i] += np.where(b0==i, (1 - b), 0)
        temp_coefs[:, :, i] += np.where(b1==i, b, 0)
    
    return temp_coefs


def per_pixel_hog(image, dy=2, dx=2, signed_orientation=False, nbins=9, flatten=False, normalise=True):
    gx, gy = gradient(image, same_size=True)
    magnitude, orientation = magnitude_orientation(gx, gy)
    sy, sx = image.shape
    orientations_image = interpolate_orientation(orientation, sx, sy, nbins, signed_orientation)
    for j in range(1, dy):
        for i in range(1, dx):
            orientations_image[:-j, :-i, :] += orientations_image[j:, i:, :]
    
    if normalise:
        normalised_blocks = normalise_histogram(orientations_image, 1, 1, 1, 1, nbins)
    else:
        normalised_blocks = orientations_image
    
    if flatten:
        normalised_blocks = normalised_blocks.flatten()

    return normalised_blocks


def interpolate(magnitude, orientation, csx, csy, sx, sy, n_cells_x, n_cells_y, signed_orientation=False, nbins=9):
    dx = csx//2
    dy = csy//2
    
    temp_coefs = interpolate_orientation(orientation, sx, sy, nbins, signed_orientation)


    # Coefficients of the spatial interpolation in every direction
    coefs = compute_coefs(csx, csy, dx, dy, n_cells_x, n_cells_y)
    
    temp = np.zeros((sy, sx, nbins))
    # hist(y0, x0)
    temp[:-dy, :-dx, :] += temp_coefs[dy:, dx:, :]*\
        (magnitude[dy:, dx:]*coefs[-(n_cells_y*csy - dy):, -(n_cells_x*csx - dx):])[:, :, np.newaxis]
    
    # hist(y1, x0)
    coefs = np.rot90(coefs)
    temp[dy:, :-dx, :] += temp_coefs[:-dy, dx:, :]*\
        (magnitude[:-dy, dx:]*coefs[:(n_cells_y*csy - dy), -(n_cells_x*csx - dx):])[:, :, np.newaxis]
    
    # hist(y1, x1)
    coefs = np.rot90(coefs)
    temp[dy:, dx:, :] += temp_coefs[:-dy, :-dx, :]*\
        (magnitude[:-dy, :-dx]*coefs[:(n_cells_y*csy - dy), :(n_cells_x*csx - dx)])[:, :, np.newaxis]
    
    # hist(y0, x1)
    coefs = np.rot90(coefs)
    temp[:-dy, dx:, :] += temp_coefs[dy:, :-dx, :]*\
        (magnitude[dy:, :-dx]*coefs[-(n_cells_y*csy - dy):, :(n_cells_x*csx - dx)])[:, :, np.newaxis]
    
    # Compute the histogram: sum over the cells
    orientation_histogram = temp.reshape((n_cells_y, csy, n_cells_x, csx, nbins)).sum(axis=3).sum(axis=1)
    
    return orientation_histogram

def normalise_histogram(orientation_histogram, bx, by, n_cells_x, n_cells_y, nbins):
    eps = 1e-7
    
    if bx==1 and by==1: #faster version
        normalised_blocks = np.clip(
          orientation_histogram / np.sqrt(orientation_histogram.sum(axis=-1)**2 + eps)[:, :, np.newaxis], 0, 0.2)
        normalised_blocks /= np.sqrt(normalised_blocks.sum(axis=-1)**2 + eps)[:, :, np.newaxis]
        
    else:
        n_blocksx = (n_cells_x - bx) + 1
        n_blocksy = (n_cells_y - by) + 1
        normalised_blocks = np.zeros((n_blocksy, n_blocksx, nbins))

        for x in range(n_blocksx):
            for y in range(n_blocksy):
                block = orientation_histogram[y:y + by, x:x + bx, :]
                normalised_blocks[y, x, :] = np.clip(block[0, 0, :] / np.sqrt(block.sum()**2 + eps), 0, 0.2)
                normalised_blocks[y, x, :] /= np.sqrt(normalised_blocks[y, x, :].sum()**2 + eps)

    return normalised_blocks


def build_histogram(magnitude, orientation, cell_size=(8, 8), signed_orientation=False,
         nbins=9, cells_per_block=(1, 1), visualise=False, flatten=False, normalise=True):
    sy, sx = magnitude.shape
    csy, csx = cell_size
    
    # Consider only the right part of the image
    # (if the rest doesn't fill a whole cell, just drop it)
    sx -= sx % csx
    sy -= sy % csy
    n_cells_x = sx//csx
    n_cells_y = sy//csy
    magnitude = magnitude[:sy, :sx]
    orientation = orientation[:sy, :sx]
    by, bx = cells_per_block
    
    orientation_histogram = interpolate(magnitude, orientation, csx, csy, sx, sy, n_cells_x, n_cells_y, signed_orientation, nbins)
    
    if normalise:
        normalised_blocks = normalise_histogram(orientation_histogram, bx, by, n_cells_x, n_cells_y, nbins)
    else:
        normalised_blocks = orientation_histogram
    
    if flatten:
        normalised_blocks = normalised_blocks.flatten()

    return normalised_blocks


def histogram_from_gradients(gradientx, gradienty, cell_size=(8, 8), cells_per_block=(1, 1), signed_orientation=False,
        nbins=9, visualise=False, normalise=True, flatten=False, same_size=False):
    magnitude, orientation = magnitude_orientation(gradientx, gradienty)
    return build_histogram(magnitude, orientation, cell_size=cell_size,
         signed_orientation=signed_orientation, cells_per_block=cells_per_block,
         nbins=nbins, visualise=visualise, normalise=normalise, flatten=flatten)


def hog(image, cell_size=(8, 8), cells_per_block=(1, 1), signed_orientation=False,
        nbins=9, visualise=False, normalise=True, flatten=False, same_size=True):
    gx, gy = gradient(image, same_size=same_size)
    return histogram_from_gradients(gx, gy, cell_size=cell_size,
         signed_orientation=signed_orientation, cells_per_block=cells_per_block,
         nbins=nbins, visualise=visualise, normalise=normalise, flatten=flatten)