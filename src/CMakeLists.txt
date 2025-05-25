# Define the core data library
add_library(core_data
    core/data/reading.cpp
    core/data/text.cpp
    core/encoding/text_terms.cpp
    core/encoding/features.cpp
)

# Define the bayesian models library
add_library(models_bayesian
    models/bayesian/naive_bayes.cpp
)
add_library(models_knn
    models/knn/knn.cpp
)

add_library(models_lr
    models/linear/lr.cpp
)
# Link dependencies - bayesian models need core data functionality
target_link_libraries(models_bayesian PRIVATE core_data)
target_link_libraries(models_knn PRIVATE core_data)
target_link_libraries(models_lr PRIVATE core_data)
# Create the main executable for the naive bayes example
add_executable(naive_bayes_app models/bayesian/main.cpp)
add_executable(knn_app models/knn/main.cpp)
add_executable(lr_app models/linear/main.cpp)

target_link_libraries(naive_bayes_app PRIVATE models_bayesian core_data)
target_link_libraries(knn_app PRIVATE models_knn core_data)
target_link_libraries(lr_app PRIVATE models_lr core_data)
