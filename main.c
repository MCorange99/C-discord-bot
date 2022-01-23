#include <stdio.h>
#include "discord.h"

void on_ready(struct discord* client) {
  const struct discord_user *bot = discord_get_self(client);

  log_info("Logged in as %s!", bot->username);
}

void ping(struct discord *client, const struct discord_message *msg) {
  if (msg->author->bot) return;

  struct discord_create_message_params params = { .content = "pong!" }; // message content
  discord_create_message(client, msg->channel_id, &params, NULL); // send response
}

int main(void) {
  struct discord *client = discord_config_init("config.json");

  discord_set_on_ready(client, &on_ready);
  discord_set_on_command(client, "pong", &ping);
  fgetc(stdin); // wait for input
  discord_run(client);

  discord_cleanup(client);

  return 0;
}
