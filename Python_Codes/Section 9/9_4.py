new_basis = U[:, 0:3]
plt.plot(new_basis)
plt.show()

S_matrix = np.zeros([3, 80])
S_matrix[0:3, 0:3] = np.diag(S[0:3])
proj = np.matmul(np.dot(new_basis, S_matrix), Vt[:, 0:3])

if new_basis.shape[1] == 3:
    fig=plt.figure(figsize=(10,5))
    ax = fig.add_subplot(111, projection='3d')
    for i in range(len(all_words_arr)):
        Axes3D.scatter(ax, *proj[i*num_samples_train:num_samples_train*(i+1)].T, c=cm[i], marker = 'o', s=20)
    plt.legend(all_words_arr,loc='center left', bbox_to_anchor=(1.07, 0.5))
    
    fig, axs = plt.subplots(1, 3, figsize=(15,5))
    for i in range(len(all_words_arr)):
        axs[0].scatter(proj[i*num_samples_train:num_samples_train*(i+1),0], proj[i*num_samples_train:num_samples_train*(i+1),1], c=cm[i], edgecolor='none')
        axs[1].scatter(proj[i*num_samples_train:num_samples_train*(i+1),0], proj[i*num_samples_train:num_samples_train*(i+1),2], c=cm[i], edgecolor='none')
        axs[2].scatter(proj[i*num_samples_train:num_samples_train*(i+1),1], proj[i*num_samples_train:num_samples_train*(i+1),2], c=cm[i], edgecolor='none')
    axs[0].set_title("View 1")
    axs[1].set_title("View 2")
    axs[2].set_title("View 3")
    plt.legend(all_words_arr,loc='center left', bbox_to_anchor=(1, 0.5))
    plt.show()
    
elif new_basis.shape[1] == 2:
    fig=plt.figure(figsize=(10,5))
    for i in range(len(all_words_arr)):
        plt.scatter(proj[i*num_samples_train:num_samples_train*(i+1),0], proj[i*num_samples_train:num_samples_train*(i+1),1], edgecolor='none')

    plt.legend(selected_words_arr,loc='center left', bbox_to_anchor=(1, 0.5))
    plt.show()


selected_words_arr = ['apple', 'back', 'watermelon', 'forward']

# Select data
selected_train_dict = {k: train_dict[k] for k in selected_words_arr}
selected_processed_train_dict = {k: processed_train_dict[k] for k in selected_words_arr}
selected_test_dict = {k: test_dict[k] for k in selected_words_arr}

num_samples_train = min(list(map(lambda x : np.shape(x)[0], selected_train_dict.values())))
num_samples_test = min(list(map(lambda x : np.shape(x)[0], selected_test_dict.values())))
print(num_samples_train)
# Reconstruct and demean data based on 4 chosen words.
# Zero-mean the matrix new A

processed_A = np.vstack(list(selected_processed_train_dict.values()))
mean_vec = np.mean(processed_A, axis = 0)
demeaned_A = np.zeros(np.shape(processed_A))
for i in np.arange(len(mean_vec)):
    demeaned_A[:, i] = processed_A[:, i] - mean_vec[i]
#demeaned_A = demeaned_A[:, 0:3]
print(demeaned_A[0:3])
print(processed_A.shape)
print(mean_vec.shape)
print(demeaned_A.shape)