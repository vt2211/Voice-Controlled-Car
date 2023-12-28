all_words_arr = ['back', 'forward', 'banana', 'watermelon', 'turnleft', 'apple']
train_test_split_ratio = 0.7
train_dict = {}
test_dict = {}

for i in range(len(all_words_arr)):
    word_raw = utils.read_csv("PCA_data/{}.csv".format(all_words_arr[i]))
    word_raw_train, word_raw_test = utils.train_test_split(word_raw, train_test_split_ratio)
    train_dict[all_words_arr[i]] = word_raw_train
    test_dict[all_words_arr[i]] = word_raw_test

# Count the minimum number of samples across the six recorded words
num_samples_train = min(list(map(lambda x : np.shape(x)[0], train_dict.values())))
num_samples_test = min(list(map(lambda x : np.shape(x)[0], test_dict.values())))

# Crop the number of samples for each word to the minimum number so all words have the same number of samples.
for key, raw_word in train_dict.items():
    train_dict[key] = raw_word[:num_samples_train,:]

for key, raw_word in test_dict.items():
    test_dict[key] = raw_word[:num_samples_test,:]
    
word_number = 0
selected_words_arr = all_words_arr
for word_raw_train in train_dict.values():
    plt.plot(word_raw_train.T)
    plt.title('Training sample for "{}"'.format(selected_words_arr[word_number]))
    word_number += 1
    plt.show()