#ifndef _APP_WORKERS_WORKER_HPP_
#define _APP_WORKERS_WORKER_HPP_

#include <string>
#include <armadillo>
#include <functional>
#include <iostream>
#include <rdkafka.h>

namespace workers
{
    class Worker
    {
        private:
            std::string brokers;
            std::string kafka_topic_name;
            rd_kafka_topic_t *kafkaTopic;
            int kafkaPartition = RD_KAFKA_PARTITION_UA;
            rd_kafka_resp_err_t kafkaError;
            rd_kafka_conf_t *kafkaConfig;
            rd_kafka_topic_conf_t *topicConfig;
            rd_kafka_t *kafka;

        public:
            Worker( std::string name, std::string address );
            std::string get_kafka_topic();
            void publish_data(arma::mat *recv_matrix);
    };
}

#endif //  _APP_WORKERS_WORKER_HPP_
