word_number = 0
for word_raw_test in selected_test_dict.values():
    plt.plot(word_raw_test.T)
    plt.title('Test sample for "{}"'.format(selected_words_arr[word_number]))
    word_number += 1
    plt.show()

processed_test_dict = process_data(selected_test_dict, length, pre_length, threshold)

selected_processed_test_dict = {k: processed_test_dict[k] for k in selected_words_arr}
processed_A_test = np.vstack(list(selected_processed_test_dict.values()))

projected_mean_vec = mean_vec.dot(new_basis[0:80]) #
projected_A_test = processed_A_test.dot(new_basis[0:80]) #project test data onto the same basis as train data

#Zero mean the test data using projected_mean_vec
proj = np.zeros(np.shape(projected_A_test))
for i in np.arange(len(projected_mean_vec)):
    proj[:, i] = projected_A_test[:, i] - projected_mean_vec[i]
    
#Plot projections
if new_basis.shape[1] == 3:
    fig=plt.figure(figsize=(10,7))
    ax = fig.add_subplot(111, projection='3d')
    for i in range(len(selected_words_arr)):
        Axes3D.scatter(ax, *proj[i*num_samples_test:num_samples_test*(i+1)].T, c=cm[i], marker = 'o', s=20)
    plt.legend(selected_words_arr,loc='center left', bbox_to_anchor=(1.07, 0.5))
    plt.title("Test Data")
    for i in range(len(selected_words_arr)):
        Axes3D.scatter(ax, *np.array([centroids[i]]).T, c=cm[i], marker = '*', s=300)
    
    fig, axs = plt.subplots(1, 3, figsize=(15,5))
    for i in range(len(selected_words_arr)):
        axs[0].scatter(proj[i*num_samples_test:num_samples_test*(i+1),0], proj[i*num_samples_test:num_samples_test*(i+1),1], c=cm[i], edgecolor='none')
        axs[1].scatter(proj[i*num_samples_test:num_samples_test*(i+1),0], proj[i*num_samples_test:num_samples_test*(i+1),2], c=cm[i], edgecolor='none')
        axs[2].scatter(proj[i*num_samples_test:num_samples_test*(i+1),1], proj[i*num_samples_test:num_samples_test*(i+1),2], c=cm[i], edgecolor='none')
    axs[0].set_title("View 1")
    axs[1].set_title("View 2")
    axs[2].set_title("View 3")
    plt.legend(selected_words_arr, loc='center left', bbox_to_anchor=(1, 0.5))
    axs[0].scatter(centroid_list[:,0], centroid_list[:,1], c=colors, marker='*', s=300)
    axs[1].scatter(centroid_list[:,0], centroid_list[:,2], c=colors, marker='*', s=300)
    axs[2].scatter(centroid_list[:,1], centroid_list[:,2], c=colors, marker='*', s=300)
    fig.show()

elif new_basis.shape[1] == 2:
    fig=plt.figure(figsize=(10,7))
    for i in range(len(selected_words_arr)):
        plt.scatter(proj[i*num_samples_test:num_samples_test*(i+1),0], proj[i*num_samples_test:num_samples_test*(i+1),1], c=colors[i], edgecolor='none')

    plt.scatter(centroid_list[:,0], centroid_list[:,1], c=colors, marker='*', s=300)
    plt.legend(selected_words_arr,loc='center left', bbox_to_anchor=(1, 0.5))
    plt.title("Test Data")
    plt.show()

def classify(data_point, new_basis, projected_mean_vec, centroids):
    projected_data_point = np.dot(data_point, new_basis)
    demeaned = projected_data_point - projected_mean_vec
    distances = list(map(np.linalg.norm, centroid_list - demeaned))
    return np.argmin(distances) + 1

correct_counts = np.zeros(4)

for (row_num, data) in enumerate(processed_A_test):
    word_num = row_num // num_samples_test + 1
    if classify(data) == word_num:
        correct_counts[word_num - 1] += 1
        
for i in range(len(correct_counts)):
    print("Percent correct of word {} = {}%".format(i + 1, 100 * correct_counts[i] / num_samples_test))