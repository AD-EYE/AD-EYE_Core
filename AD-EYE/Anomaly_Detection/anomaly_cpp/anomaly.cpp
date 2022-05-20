#include <torch/torch.h>
#include <cstddef>
#include <cstdio>
#include <string>
#include <vector>

// const char* kDataRoot = "./dataset"

const int64_t hidden_layer_1 = 256;
const int64_t hidden_layer_2 = 128;
const int64_t channels = 1;
const int64_t kernel_size = 3;
const int64_t image_size = 128;
const int64_t epochs = 10;
const int64_t batch_size = 8;
// const int64_t kLogInterval = 10;

const char* kDataRoot = "./data"; 
const int64_t kTrainBatchSize = 64 ;
const int64_t kTestBatchSize = 1000;
const int64_t kNumberOfEpochs = 10;
const int64_t kLogInterval = 10;

struct Net : torch::nn::Module {
    Net()
        : conv1(torch::nn::Conv2dOptions(image_size, hidden_layer_1, kernel_size).stride(2).padding(2)), 
          conv2(torch::nn::Conv2dOptions(hidden_layer_1, hidden_layer_2, kernel_size).stride(2).padding(2)),
          
          conv1t(torch::nn::ConvTranspose2dOptions(hidden_layer_1, hidden_layer_2, kernel_size).stride(2).padding(2)),
          conv2t(torch::nn::ConvTranspose2dOptions(hidden_layer_2, hidden_layer_1, kernel_size).stride(2).padding(2)),
          conv3t(torch::nn::ConvTranspose2dOptions(hidden_layer_1, image_size, kernel_size).stride(2).padding(2))
          {
              register_module("conv1", conv1);
              register_module("conv2", conv2);
              register_module("conv1t", conv1t);
              register_module("conv2t", conv2t);
              register_module("conv3t", conv3t);
          }
    torch::Tensor forward(torch::Tensor x){
        x = torch::relu(conv1->forward(x));
        x = torch::relu(conv2->forward(x));
        x = torch::relu(conv1t->forward(x));
        x = torch::relu(conv2t->forward(x));

        x = torch::relu(conv3t->forward(x));
        
        return torch::sigmoid(x);
    }

    torch::nn::Conv2d conv1;
    torch::nn::Conv2d conv2;
    torch::nn::ConvTranspose2d conv1t;
    torch::nn::ConvTranspose2d conv2t;
    torch::nn::ConvTranspose2d conv3t;
};


// struct Net : torch::nn::Module {
//     Net() 
//         : conv1(torch::nn::Conv2dOptions(1, 10, 5)),
//           conv2(torch::nn::Conv2dOptions(10, 20, 5)),
//           fc1 (320, 50), 
//           fc2 (50, 10){
//     register_module("conv1", conv1);
//     register_module("conv2", conv2);
//     register_module("conv2_drop", conv2_drop);
//     register_module("fc1", fc1);
//     register_module("fc21", fc1);
//     }

//     torch::Tensor forward(torch::Tensor x) {
//         x = torch::relu(torch::max_pool2d(conv1->forward(x), 2));
//         x = torch::relu(torch::max_pool2d(conv2_drop->forward(conv2->forward(x)), 2));
//         x = x.view({-1, 320});
//         x = torch::relu(fc1->forward(x));
//         x = torch::dropout(x, 0.5, is_training());
//         x = fc2->forward(x);
//         return torch::log_softmax(x, 1);

//     }  

//     torch::nn::Conv2d conv1; 
//     torch::nn::Conv2d conv2; 
//     torch::nn::Dropout2d conv2_drop; 
//     torch::nn::Linear fc1;
//     torch::nn::Linear fc2;  
// };


template <typename DataLoader>
void train(
    size_t epoch, 
    Net& model, 
    torch::Device device, 
    DataLoader& data_loader, 
    torch::optim::Optimizer& optimizer, 
    size_t dataset_size) {
        model.train();
        size_t batch_idx = 0;
        for (auto& batch : data_loader) {
            auto data = batch.data.to(device), targets = batch.data.to(device);
            optimizer.zero_grad();
            auto output = model.forward(data);
            // std::cout<<output<<std::endl;
            // std::cout<<targets<<std::endl;
            auto loss = torch::nll_loss(output, targets);
            std::cout<<loss<<std::endl;
            AT_ASSERT(!std::isnan(loss.template item<float>()));
            loss.backward();
            optimizer.step();
            
        if (batch_idx++ % kLogInterval == 0) {
        std::printf(
            "\rTrain Epoch: %ld [%5ld/%5ld] Loss: %.4f",
            epoch,
            batch_idx * batch.data.size(0),
            dataset_size,
            loss.template item<float>());
            }
    }
    }

template <typename DataLoader>
void test(
    Net& model, 
    torch::Device device, 
    DataLoader& data_loader, 
    size_t dataset_size){
        torch::NoGradGuard no_grad;
        model.eval();
        double test_loss = 0;
        int32_t correct = 0;
        for (const auto& batch : data_loader){
            auto data = batch.data.to(device), targets = batch.data.to(device);
            auto output = model.forward(data);
            std::cout<<output<<std::endl;
            test_loss += torch::nll_loss(
                output, 
                targets, 
                {}, 
                torch::Reduction::Sum)
                .template item <float>();
        auto pred = output.argmax(1);
        correct += pred.eq(targets).sum().template item<int64_t>();
        }

        test_loss /= dataset_size;
        std::printf(
            "\nTest set: Average loss: %.4f  | Acuracy: %.3f\n", 
            test_loss, 
            static_cast <double> (correct) / dataset_size);
    }
auto main() -> int {
    torch::manual_seed(1);
    torch::DeviceType device_type;
    if (torch::cuda::is_available()){
        std::cout<<"CUDA available! Traiing on GPU. " <<std::endl;
        device_type = torch::kCUDA;
    } else {
        std::cout << "Training on CPU." << std::endl;
        device_type = torch::kCPU;
    }
    torch::Device device(device_type);

    Net model;
    model.to(device);

    auto train_dataset = torch::data::datasets::MNIST(kDataRoot)
                                .map(torch::data::transforms::Normalize<>(0.1307, 0.3081))
                                .map(torch::data::transforms::Stack<>());
    const size_t train_dataset_size = train_dataset.size().value();
    auto train_loader = 
        torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(
            std::move(train_dataset), kTrainBatchSize);
    auto test_dataset = torch::data::datasets::MNIST (
        kDataRoot, torch::data::datasets::MNIST::Mode::kTest)
        .map(torch::data::transforms::Normalize<>(0.1307, 0.3081))
        .map(torch::data::transforms::Stack<>());

    const size_t test_dataset_size = test_dataset.size().value();
    auto test_loader = torch::data::make_data_loader(std::move(test_dataset), kTestBatchSize);
    torch::optim::SGD optimizer(
        model.parameters(), torch::optim::SGDOptions(0.01).momentum(0.5));

    for (size_t epoch = 1; epoch <=kNumberOfEpochs; ++epoch){
        train(epoch, model, device, *train_loader, optimizer, train_dataset_size);
        test(model, device, *test_loader, test_dataset_size);
    }
    }