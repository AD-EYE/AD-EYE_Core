#include <iostream>
#include <torch/torch.h>

int main()
{
    torch::Tensor tensor = torch::rand({2, 3});
    std::cout <<"this is a test"<<std::endl;
    std::cout << tensor << std::endl;
}