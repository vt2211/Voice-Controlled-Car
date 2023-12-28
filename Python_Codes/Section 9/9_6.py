def find_centroids(clustered_data, num_samples_train):
    centroids = []
    for i in range(4):
        centroids.append([np.mean(clustered_data[i*num_samples_train:(1+i)*num_samples_train, 0]), np.mean(clustered_data[i*num_samples_train:(1+i)*num_samples_train, 1]),np.mean(clustered_data[i*num_samples_train:(1+i)*num_samples_train, 2])])
    return centroids

centroid_list = np.vstack(centroids)
colors = cm[:(len(centroids))]

for i, centroid in enumerate(centroid_list):
    print('Centroid {} is at: {}'.format(i, str(centroid)))

if new_basis.shape[1] == 3:
    fig=plt.figure(figsize=(10,7))
    ax = fig.add_subplot(111, projection='3d')
    for i in range(len(selected_words_arr)):
        Axes3D.scatter(ax, *proj[i*num_samples_train:num_samples_train*(i+1)].T, c=cm[i], marker = 'o', s=20)
    plt.legend(selected_words_arr, loc='center left', bbox_to_anchor=(1.07, 0.5))
    for i in range(len(selected_words_arr)):
        Axes3D.scatter(ax, *np.array([centroids[i]]).T, c=cm[i], marker = '*', s=300)
    plt.title("Training Data")
    
    fig, axs = plt.subplots(1, 3, figsize=(15,5))
    for i in range(len(selected_words_arr)):
        axs[0].scatter(proj[i*num_samples_train:num_samples_train*(i+1),0], proj[i*num_samples_train:num_samples_train*(i+1),1], c=cm[i], edgecolor='none')
        axs[1].scatter(proj[i*num_samples_train:num_samples_train*(i+1),0], proj[i*num_samples_train:num_samples_train*(i+1),2], c=cm[i], edgecolor='none')
        axs[2].scatter(proj[i*num_samples_train:num_samples_train*(i+1),1], proj[i*num_samples_train:num_samples_train*(i+1),2], c=cm[i], edgecolor='none')
    axs[0].set_title("View 1")
    axs[1].set_title("View 2")
    axs[2].set_title("View 3")
    plt.legend(selected_words_arr, loc='center left', bbox_to_anchor=(1, 0.5))
    axs[0].scatter(centroid_list[:,0], centroid_list[:,1], c=colors, marker='*', s=300)
    axs[1].scatter(centroid_list[:,0], centroid_list[:,2], c=colors, marker='*', s=300)
    axs[2].scatter(centroid_list[:,1], centroid_list[:,2], c=colors, marker='*', s=300)
    plt.show()

elif new_basis.shape[1] == 2:
    fig=plt.figure(figsize=(10,7))
    for i in range(len(selected_words_arr)):
        plt.scatter(proj[i*num_samples_train:num_samples_train*(i+1),0], proj[i*num_samples_train:num_samples_train*(i+1),1], c=colors[i], edgecolor='none')

    plt.scatter(centroid_list[:,0], centroid_list[:,1], c=colors, marker='*', s=300)
    plt.legend(selected_words_arr,loc='center left', bbox_to_anchor=(1, 0.5))
    plt.title("Training Data")
    plt.show()
    