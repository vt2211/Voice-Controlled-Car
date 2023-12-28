processed_A = np.vstack(list(processed_train_dict.values()))
mean_vec = np.mean(processed_A, axis = 0)
demeaned_A = np.zeros(np.shape(processed_A))
for i in np.arange(len(mean_vec)):
    demeaned_A[:, i] = processed_A[:, i] - mean_vec[i]



