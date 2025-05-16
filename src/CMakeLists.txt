# Define the core data library
add_library(core_data
    core/data/reading.cpp
    core/data/splitting.cpp
    core/data/text.cpp
)

# Define the bayesian models library
add_library(models_bayesian
    models/bayesian/naive_bayes.cpp
)

# Link dependencies - bayesian models need core data functionality
target_link_libraries(models_bayesian PRIVATE core_data)

# Create the main executable for the naive bayes example
add_executable(naive_bayes_app models/bayesian/main.cpp)

target_link_libraries(naive_bayes_app PRIVATE models_bayesian core_data)
