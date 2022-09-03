#include "dds_pubsub.h"

#define MAX_SAMPLES 1
/**
 * @brief Function to bind publish for zeromq.
 * @param Handlerstruct Handle strucure with all required data.
 * @return void..
 */
void ddspub_bind(Handlerstruct *me)
{
  dds_entity_t participant;
  dds_entity_t topic;
  dds_entity_t writer;
  dds_return_t rc;
  uint32_t status = 0;
  dds_qos_t *qos;
  dds_qos_t *qos1;

  qos1 = dds_create_qos ();
  dds_qset_reliability (qos, DDS_RELIABILITY_RELIABLE, DDS_SECS (10));

  /* Create a Participant. */
  participant = dds_create_participant (DDS_DOMAIN_DEFAULT, qos1, NULL);
  if (participant < 0)
    DDS_FATAL("dds_create_participant: %s\n", dds_strretcode(-participant));

  dds_delete_qos(qos1);
  /* Create a Topic. */
  topic = dds_create_topic (
    participant, &Pubsub_gen_Msg_desc, me->topic, NULL, NULL);
  if (topic < 0)
    DDS_FATAL("dds_create_topic: %s\n", dds_strretcode(-topic));
    /* Create a reliable Reader. */
  qos = dds_create_qos ();
  dds_qset_reliability (qos, DDS_RELIABILITY_RELIABLE, DDS_SECS (10));

  /* Create a Writer. */
  writer = dds_create_writer (participant, topic, qos, NULL);
  if (writer < 0)
    DDS_FATAL("dds_create_writer: %s\n", dds_strretcode(-writer));

  printf("=== [Publisher]  Waiting for a reader to be discovered ...\n");
  dds_delete_qos(qos);
  fflush (stdout);

  rc = dds_set_status_mask(writer, DDS_PUBLICATION_MATCHED_STATUS);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_set_status_mask: %s\n", dds_strretcode(-rc));

  while(!(status & DDS_PUBLICATION_MATCHED_STATUS))
  {
    rc = dds_get_status_changes (writer, &status);
    if (rc != DDS_RETCODE_OK)
      DDS_FATAL("dds_get_status_changes: %s\n", dds_strretcode(-rc));

    /* Polling sleep. */
    dds_sleepfor (DDS_MSECS (20));
  }

  me->sock_dds = writer;
  
}



/**
 * @brief Function to publish data with zeromq.
 * @param Handlerstruct Handle strucure with all required data.
 * @param data Data value.
 * @return int: Returns 0 if sent.
 */
void ddspublish(Handlerstruct *me, char* data) {

  Pubsub_gen_Msg msg;
  dds_return_t rc;
  dds_entity_t writer = (me->sock_dds);
 /* Create a message to write. */
  
  msg.message = data;

  printf ("=== [Publisher]  Writing : ");
  printf ("Message ( %s)\n",  msg.message);
  fflush (stdout);

  rc = dds_write (writer, &msg);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_write: %s\n", dds_strretcode(-rc));

  /* Deleting the participant will delete all its children recursively as well. */
  //rc = dds_delete (participant);
  //if (rc != DDS_RETCODE_OK)
   // DDS_FATAL("dds_delete: %s\n", dds_strretcode(-rc));

}


/**
 * @brief Function to bind subscribe for zeromq.
 * @param Handlerstruct Handle strucure with all required data.
 * @return zsock_t: Returns socket.
 */
void ddssub_bind(Handlerstruct *me)
{
  dds_entity_t participant;
  dds_entity_t topic;
  dds_entity_t reader;
  
  
  dds_return_t rc;
  dds_qos_t *qos;
  dds_qos_t *qos1;

  qos1 = dds_create_qos ();
  dds_qset_reliability (qos, DDS_RELIABILITY_RELIABLE, DDS_SECS (10));
  /* Create a Participant. */
  participant = dds_create_participant (DDS_DOMAIN_DEFAULT, qos1, NULL);
  if (participant < 0)
    DDS_FATAL("dds_create_participant: %s\n", dds_strretcode(-participant));

  dds_delete_qos(qos1);

  /* Create a Topic. */
  topic = dds_create_topic (
    participant, &Pubsub_gen_Msg_desc, me->topic, NULL, NULL);
  if (topic < 0)
    DDS_FATAL("dds_create_topic: %s\n", dds_strretcode(-topic));

  /* Create a reliable Reader. */
  qos = dds_create_qos ();
  dds_qset_reliability (qos, DDS_RELIABILITY_RELIABLE, DDS_SECS (10));
  reader = dds_create_reader (participant, topic, qos, NULL);
  if (reader < 0)
    DDS_FATAL("dds_create_reader: %s\n", dds_strretcode(-reader));
  dds_delete_qos(qos);

  printf ("\n=== [Subscriber] Waiting for a sample ...\n");
  fflush (stdout);

  me->sock_dds = reader;

}



/**
 * @brief Function to subscribe data with zeromq.
 * @param Handlerstruct Handle strucure with all required data.
 * @return char: Returns reveived data.
 */
char* ddssubscribe(Handlerstruct *me) {

  dds_entity_t reader = (me->sock_dds);
  dds_return_t rc;
  dds_sample_info_t infos[MAX_SAMPLES];
  Pubsub_gen_Msg *msg;
  void *samples[MAX_SAMPLES];
/* Initialize sample buffer, by pointing the void pointer within
   * the buffer array to a valid sample memory location. */
  
  /* Poll until data has been read. */
  while (true)
  {
    samples[0] = Pubsub_gen_Msg__alloc ();
    /* Do the actual read.
     * The return value contains the number of read samples. */
    rc = dds_take (reader, samples, infos, MAX_SAMPLES, MAX_SAMPLES);
    if (rc < 0)
      DDS_FATAL("dds_read: %s\n", dds_strretcode(-rc));

    /* Check if we read some data and it is valid. */
    if ((rc > 0) && (infos[0].valid_data))
    {
      /* Print Message. */
      msg = (Pubsub_gen_Msg*)samples[0];
      //printf ("=== [Subscriber] Received : ");
      //printf ("Message ( %s)\n",  msg->message);
      me->msgarrvd(0,me->topic,6,msg->message);
       /* Free the data location. */
      Pubsub_gen_Msg_free (samples[0], DDS_FREE_ALL);
      //fflush (stdout);
      //break;
    }
    else
    {
      /* Polling sleep. */
      dds_sleepfor (DDS_MSECS (20));
    }
  }

 

  /* Deleting the participant will delete all its children recursively as well. */
 // rc = dds_delete (participant);
  //if (rc != DDS_RETCODE_OK)
   // DDS_FATAL("dds_delete: %s\n", dds_strretcode(-rc));

}


/**
 * @brief Function to initialize the framework structure. It initializes with all the nanomsg function pointers.
 * @param structframwork Structure for framework.
 * @return void.
 */
void dds_operation_initialize(struct framwork *frame)
{
	frame->publish = &ddspublish;
	frame->subscribe = &ddssubscribe;
	frame->pub_bind =  &ddspub_bind;
	frame->sub_bind = &ddssub_bind;

}