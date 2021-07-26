# Configure Docker Credential Helper on Linux

## Problem Description

When running `docker login` on Linux, the following warning message will show up:

```
WARNING! Your password will be stored unencrypted in /home/X/.docker/config.json .
Configure a credential helper to remove this warning. See
https://docs.docker.com/engine/reference/commandline/login/#credentials-store
```

## What to Do

To get rid of this message, one can setup Docker Credential Helpers.

[Ref](https://docs.docker.com/engine/reference/commandline/login/#credentials-store)

On Linux, this can be done by the following steps.

### Step 1: Install gnupg2 and [pass](https://www.passwordstore.org)

```
sudo apt install gnupg2 pass
```

### Step 2. Install docker-credential-pass

Download it from (Release](https://github.com/docker/docker-credential-helpers/releases) page of
the [Docker Credential Helpers](https://github.com/docker/docker-credential-helpers) project.

```
wget https://github.com/docker/docker-credential-helpers/releases/download/v0.6.4/docker-credential-pass-v0.6.4-amd64.tar.gz
tar xzvf docker-credential-pass-v0.6.4-amd64.tar.gz
sudo mv docker-credential-pass /usr/local/bin/
sudo chmod +x /usr/local/bin/docker-credential-pass
```

### Step 3. Create a new GPG2 key

```
gpg2 --gen-key
```

Set "Real name" and "Email address".  For me, "Jiaming Liu" and "jiaming@qcraft.ai", respectively.

and follow prompts thereafter

### Step 4. Initialize pass with the generated key

```
pass init "<Your Name>"
# Or
pass init "<Your Email>"
```

### Step 5. Add credsStore to your docker config

Content of an empty `/home/X/.docker/config.json`:

```
{
  "credsStore": "pass"
}
```

### Step 6. Login to docker

```
docker login
```

## References

Credit to https://github.com/docker/docker-credential-helpers/issues/102#issuecomment-388974092

