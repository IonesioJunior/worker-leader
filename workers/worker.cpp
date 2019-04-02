#include "worker.hpp"


workers::Worker::Worker( std::string name, std::string address )
{
    this->brokers = address;
    this->kafka_topic_name = name;
    std::hash<std::string> str_hash;
    str_hash(name);
    char errorString[512];
    this->kafkaConfig = rd_kafka_conf_new();
    this->topicConfig = rd_kafka_topic_conf_new();
    if ( !( this->kafka = rd_kafka_new( RD_KAFKA_PRODUCER, 
                                  this->kafkaConfig, 
                                  errorString, 
                                  sizeof(errorString) ) ) ) 
    {
         fprintf( stderr, "%% Failed to create new producer: %s\n", errorString );
         exit( -1 );
    }
    if ( rd_kafka_brokers_add( this->kafka, this->brokers.c_str() ) == 0 ) 
    {
        fprintf( stderr, "%% No valid brokers specified\n" );
        exit( -1 );
    }


    this->kafkaTopic = rd_kafka_topic_new( this->kafka, this->kafka_topic_name.c_str(), this->topicConfig );
    topicConfig = NULL;
}

std::string workers::Worker::get_kafka_topic()
{
    return this->kafka_topic_name;
}


std::vector< std::vector<double> > mat_to_std_vec(arma::mat *A) {
    std::vector< std::vector<double>  > vec_mat(A->n_rows);
    for (size_t i = 0; i < A->n_rows; ++i) {
        vec_mat[i] = arma::conv_to< std::vector<double> >::from(A->row(i));
    };
    return vec_mat;
}

void workers::Worker::publish_data( arma::mat *rec_matrix )
{
    std::vector< std::vector< double> > vec_mat = mat_to_std_vec(rec_matrix);
    for(size_t i = 0; i < vec_mat.size();i++)
    {
        std::cout << vec_mat[i][0] << vec_mat[i][1] << std::endl;
    }
    while ( rd_kafka_produce(
				    		 this->kafkaTopic,
					    	 this->kafkaPartition,
						     RD_KAFKA_MSG_F_COPY,
							 rec_matrix,
						     rec_matrix->size(),
							 NULL,
							 0,
			    			 NULL) != 0 );    
}
