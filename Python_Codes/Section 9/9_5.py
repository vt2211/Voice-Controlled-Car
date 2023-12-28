U, S, Vt = np.linalg.svd(demeaned_A, full_matrices=True)
new_basis = U[:, 0:3]
S_matrix = np.zeros([3, 80])
S_matrix[0:3, 0:3] = np.diag(S[0:3])
proj = np.matmul(np.dot(new_basis, S_matrix), Vt[:, 0:3])

S_matrix = np.zeros([3, 80])
S_matrix[0:3, 0:3] = np.diag(S[0:3])
proj = np.matmul(np.dot(new_basis, S_matrix), Vt[:, 0:3])

if new_basis.shape[1] == 3:
    fig=plt.figure(figsize=(10,5))
    ax = fig.add_subplot(111, projection='3d')
    for i in range(len(selected_words_arr)):
        Axes3D.scatter(ax, *proj[i*num_samples_train:num_samples_train*(i+1)].T, c=cm[i], marker = 'o', s=20)
    plt.legend(selected_words_arr,loc='center left', bbox_to_anchor=(1.07, 0.5))
    
    fig, axs = plt.subplots(1, 3, figsize=(15,5))
    for i in range(len(selected_words_arr)):
        axs[0].scatter(proj[i*num_samples_train:num_samples_train*(i+1),0], proj[i*num_samples_train:num_samples_train*(i+1),1], c=cm[i], edgecolor='none')
        axs[1].scatter(proj[i*num_samples_train:num_samples_train*(i+1),0], proj[i*num_samples_train:num_samples_train*(i+1),2], c=cm[i], edgecolor='none')
        axs[2].scatter(proj[i*num_samples_train:num_samples_train*(i+1),1], proj[i*num_samples_train:num_samples_train*(i+1),2], c=cm[i], edgecolor='none')
    axs[0].set_title("View 1")
    axs[1].set_title("View 2")
    axs[2].set_title("View 3")
    plt.legend(selected_words_arr,loc='center left', bbox_to_anchor=(1, 0.5))
    plt.show()
    
elif new_basis.shape[1] == 2:
    fig=plt.figure(figsize=(10,5))
    for i in range(len(selected_words_arr)):
        plt.scatter(proj[i*num_samples_train:num_samples_train*(i+1),0], proj[i*num_samples_train:num_samples_train*(i+1),1], edgecolor='none')

    plt.legend(selected_words_arr,loc='center left', bbox_to_anchor=(1, 0.5))
    plt.show()