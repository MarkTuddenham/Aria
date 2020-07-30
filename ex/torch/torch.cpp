#include <aria.hpp>
#include <string>
#include <torch/torch.h>

// Define a new Module.
struct Net : torch::nn::Module
{
  Net()
  {
    // Construct and register two Linear submodules.
    fc1 = register_module("fc1", torch::nn::Linear(784, 64));
    fc2 = register_module("fc2", torch::nn::Linear(64, 32));
    fc3 = register_module("fc3", torch::nn::Linear(32, 10));
  }

  // Implement the Net's algorithm.
  torch::Tensor forward(torch::Tensor x)
  {
    // Use one of many tensor manipulation functions.
    x = torch::relu(fc1->forward(x.reshape({x.size(0), 784})));
    x = torch::dropout(x, /*p=*/0.5, /*train=*/is_training());
    x = torch::relu(fc2->forward(x));
    x = torch::log_softmax(fc3->forward(x), /*dim=*/1);
    return x;
  }

  // Use one of many "standard library" modules.
  torch::nn::Linear fc1{nullptr}, fc2{nullptr}, fc3{nullptr};
};

struct CNNNet : torch::nn::Module
{
  CNNNet()
      : cv1(torch::nn::Conv2dOptions(1, 10, 5)),
        cv2(torch::nn::Conv2dOptions(10, 20, 5)),
        fc1(4 * 4 * 20, 10)
  {
    cv1 = register_module("cv1", cv1);
    cv2 = register_module("cv2", cv2);
    fc1 = register_module("fc1", fc1);
  }

  // Implement the Net's algorithm.
  torch::Tensor forward(torch::Tensor x)
  {
    // Use one of many tensor manipulation functions.
    x = torch::relu(torch::max_pool2d(cv1->forward(x), 2));
    x = torch::relu(torch::max_pool2d(cv2->forward(x), 2));
    x = x.view({-1, 4 * 4 * 20});
    x = torch::dropout(x, /*p=*/0.5, /*training=*/is_training());
    x = torch::relu(fc1->forward(x));
    x = torch::log_softmax(x, /*dim=*/1);
    return x;
  }

  torch::nn::Linear fc1;
  torch::nn::Conv2d cv1, cv2;
};

void app()
{
  // const std::string device = "cuda";
  const std::string device = "cpu";
  const std::string base_path = "/absolute/path/here/";
  const std::string data_path = base_path + "ex/torch/mnist";
  const std::string model_path = base_path + "ex/torch/net.pt";

  // Create a new Net.
  auto net = std::make_shared<CNNNet>();
  net->to(device);

  // Create a multi-threaded data loader for the MNIST dataset.
  auto data_loader = torch::data::make_data_loader(
      torch::data::datasets::MNIST(data_path, torch::data::datasets::MNIST::Mode::kTrain)
          .map(torch::data::transforms::Normalize<>(0.1307, 0.3081))
          .map(torch::data::transforms::Stack<>()),
      /*batch_size=*/64);

  auto test_dataset =
      torch::data::datasets::MNIST(data_path, torch::data::datasets::MNIST::Mode::kTest);

  auto test_loader = torch::data::make_data_loader(
      test_dataset.map(torch::data::transforms::Normalize<>(0.1307, 0.3081))
          .map(torch::data::transforms::Stack<>()),
      /*batch_size=*/64);

  const size_t test_dataset_size = test_dataset.size().value();

  // Instantiate an SGD optimization algorithm to update our Net's parameters.
  // torch::optim::SGD optimizer(net->parameters(), /*lr=*/0.01);
  torch::optim::Adam optimizer(net->parameters(), /*lr=*/0.0001);

  for (size_t epoch = 1; epoch <= 50; ++epoch)
  {
    size_t batch_index = 0;
    float sum_loss = 0;

    // Iterate the data loader to yield batches from the dataset.
    for (auto& batch: *data_loader)
    {
      auto data = batch.data.to(device);
      auto target = batch.target.to(device);

      // Reset gradients.
      optimizer.zero_grad();

      // Execute the model on the input data.
      torch::Tensor prediction = net->forward(data);

      // Compute a loss value to judge the prediction of our model.
      torch::Tensor loss = torch::nll_loss(prediction, target);
      sum_loss += loss.cpu().item<float>();

      // Compute gradients of the loss w.r.t. the parameters of our model.
      loss.backward();
      // Update the parameters based on the calculated gradients.
      optimizer.step();

      // Output the loss and checkpoint every 100 batches.
      if (++batch_index % 100 == 0)
      {
        ARIA_TRACE("Batch: {} | Loss: {}", epoch, batch_index, loss.item<float>());
        // Serialize your model periodically as a checkpoint.
        torch::save(net, model_path);
      }
    }

    net->eval();
    double test_loss = 0;
    int32_t correct = 0;

    for (const auto& batch: *test_loader)
    {
      auto data = batch.data.to(device), targets = batch.target.to(device);
      auto output = net->forward(data);
      test_loss += torch::nll_loss(output, targets).item<float>();
      auto pred = output.argmax(1);
      correct += pred.eq(targets).sum().template item<int64_t>();
    }

    test_loss /= test_dataset_size;
    ARIA_INFO(
        "Epoch: {} | Average Loss: {} | Test: Average loss: {} | Accuracy: {}",
        epoch,
        sum_loss / batch_index,
        test_loss,
        static_cast<double>(correct) / test_dataset_size);
  }
}

int main()
{
  Aria::Log::init(Aria::Log::Level::TRACE);

  app();
}