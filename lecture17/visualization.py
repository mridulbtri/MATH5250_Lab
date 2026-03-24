import numpy as np
import matplotlib.pyplot as plt
# Load the original grayscale image
original_image = np.loadtxt("original_image.csv", delimiter=",", dtype=int)
# Load the blurred grayscale image
blurred_image = np.loadtxt("blurred_image.csv", delimiter=",", dtype=int)
# Plot the original grayscale image
plt.figure(figsize=(10, 5))
plt.subplot(1, 2, 1)
plt.title("Original Grayscale Image")
plt.imshow(original_image, cmap="gray", vmin=0, vmax=255)
# Plot the blurred grayscale image
plt.subplot(1, 2, 2)
plt.title("Blurred Grayscale Image")
plt.imshow(blurred_image, cmap="gray", vmin=0, vmax=255)
plt.tight_layout()
plt.show()