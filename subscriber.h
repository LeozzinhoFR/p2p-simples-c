#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

// Estrutura para a lista de inscrições de um peer
typedef struct SubscriptionNode {
    char* topic_name;
    struct SubscriptionNode* next;
} SubscriptionNode;

// Protótipos das Funções
void publish(const char* topic_name, const char* message);
void subscribe(SubscriptionNode** head, const char* topic_name);
void unsubscribe(SubscriptionNode** head, const char* topic_name);
void view_messages(SubscriptionNode* head, const char* peer_id);
void cleanup_subscriptions(SubscriptionNode** head);

#endif // SUBSCRIBER_H