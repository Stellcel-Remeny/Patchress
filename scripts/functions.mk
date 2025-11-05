define get_hash
	if [ -f "$(strip $(1))" ]; then \
	    shasum "$(strip $(1))" | cut -d ' ' -f 1; \
	fi
endef

define get_hash_dir
	if [ -d "$(strip $(1))" ]; then \
	    find "$(strip $(1))" -type f -exec stat --format="%s %Y %n" {} + | sort | shasum | cut -d ' ' -f 1; \
	fi
endef

define save_hash
	@$(call inf, Saving hash of file '$(strip $(2))' as '$(strip $(1))=')
	$(Q)"$(SCRIPTS)/set_var.sh" "$(strip $(1))" `$(call get_hash, $(2))` "$(CONF)/hashes.txt"
endef

define save_hash_dir
	@$(call inf, Saving hash of directory '$(strip $(2))' as '$(strip $(1))=')
	$(Q)"$(SCRIPTS)/set_var.sh" "$(strip $(1))" `$(call get_hash_dir, $(2))` "$(CONF)/hashes.txt"
endef